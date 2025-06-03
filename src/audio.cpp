
#define DR_WAV_IMPLEMENTATION
#include "audio.h"
#include "dr_wav.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

void AppContext::loadSamples(const char* path)
{
    unsigned int channels, sampleRate;
    drwav_uint64 totalSampleCount;

    // Read entire WAV into float PCM frames (interleaved if >1 channel)
    float* raw = drwav_open_file_and_read_pcm_frames_f32(
        path,
        &channels,
        &sampleRate,
        &totalSampleCount,
        nullptr
    );
    if (!raw) {
        return; // failed to load
    }

    // Convert to mono by averaging channels
    samples.clear();
    samples.reserve((size_t)totalSampleCount);
    for (drwav_uint64 i = 0; i < totalSampleCount; ++i) {
        float mix = 0.0f;
        for (unsigned int c = 0; c < channels; ++c) {
            mix += raw[i * channels + c];
        }
        samples.push_back(mix / (float)channels);
    }

    drwav_free(raw, nullptr);
    scroll = 0;
    zoom   = 1.0f;
}

bool AppContext::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return false;

    window = SDL_CreateWindow(
        "Waveform Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (!window)
        return false;

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context)
        return false;

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // vsync on

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // optional: keyboard nav

    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

void AppContext::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    if (gl_context) {
        SDL_GL_DeleteContext(gl_context);
        gl_context = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void AppContext::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void AppContext::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void AppContext::endFrame()
{
    ImGui::Render();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}
