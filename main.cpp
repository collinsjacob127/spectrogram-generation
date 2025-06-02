// main.cpp
#include <iostream>
#include <vector>
#include <cmath>

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include "tinyfiledialogs.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>

std::vector<float> LoadWavSamples(const char* filename) {
    unsigned int channels;
    unsigned int sampleRate;
    drwav_uint64 totalSampleCount;
    float* samples = drwav_open_file_and_read_pcm_frames_f32(
        filename, &channels, &sampleRate, &totalSampleCount, nullptr);
    if (!samples) return {};

    std::vector<float> monoSamples;
    monoSamples.reserve(totalSampleCount);
    for (drwav_uint64 i = 0; i < totalSampleCount; ++i) {
        float mix = 0;
        for (unsigned int c = 0; c < channels; ++c)
            mix += samples[i * channels + c];
        monoSamples.push_back(mix / channels);
    }
    drwav_free(samples, nullptr);
    return monoSamples;
}

int main(int, char**) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Waveform Viewer", 100, 100, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    std::vector<float> samples;
    float zoom = 1.0f;
    int scroll = 0;

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) done = true;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Waveform Controls");
        if (ImGui::Button("Load WAV")) {
            const char* file = tinyfd_openFileDialog("Open WAV", "", 0, NULL, NULL, 0);
            if (file) samples = LoadWavSamples(file);
        }
        ImGui::SliderFloat("Zoom", &zoom, 1.0f, 20.0f);
        ImGui::SliderInt("Scroll", &scroll, 0, std::max(0, (int)samples.size() - 100));
        ImGui::End();

        ImGui::Begin("Waveform");
        if (!samples.empty()) {
            int displayCount = std::max(100, (int)(samples.size() / zoom));
            int start = std::min(scroll, (int)samples.size() - displayCount);
            ImGui::PlotLines("", samples.data() + start, displayCount, 0, NULL, -1.0f, 1.0f, ImVec2(0, 150));
        }
        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

