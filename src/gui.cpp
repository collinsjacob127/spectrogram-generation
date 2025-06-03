#include "gui.h"
#include "tinyfiledialogs.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

void renderMainWindow(AppContext& app)
{
    initializeWindow(app);

    // Menu Bar (File -> Select .wav file)
    if (ImGui::BeginMenuBar())
        handleMenuBar(app);

    handleViewportControls(app);

    handleWaveformViewer(app);

    ImGui::End(); // End "Waveform Viewer"
    
}

void initializeWindow(AppContext& app) {
    // 1) Get the main viewport (the entire application window)
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 vpPos  = viewport->Pos;   // Top-left corner of application window
    ImVec2 vpSize = viewport->Size;  // Full size of application window

    // 2) Set window flags to remove all decorations and prevent moving/resizing
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDecoration         // No title bar, no resize, no collapse
      | ImGuiWindowFlags_NoMove               // Cannot be moved
      | ImGuiWindowFlags_NoResize             // Cannot be resized by user
      | ImGuiWindowFlags_NoBringToFrontOnFocus
      | ImGuiWindowFlags_MenuBar              // Include the menu bar
      | ImGuiWindowFlags_NoSavedSettings;     // Don’t store/restor user settings

    // 3) Force next window to cover the entire viewport (the SDL/GL window)
    ImGui::SetNextWindowPos(vpPos);
    ImGui::SetNextWindowSize(vpSize);
    // ImGui::SetNextWindowViewport(viewport->ID);

    // 4) Begin the single "Waveform Viewer" window with these flags
    ImGui::Begin("Waveform Viewer", nullptr, window_flags);
}

void handleMenuBar(AppContext& app) {
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Select .wav file"))
        {
            // Select filepath with tinyfd
            const char* filePath = tinyfd_openFileDialog(
                "Open WAV File",
                "../wav-files/",
                0, NULL, NULL,
                0
            );

            // Verify and handle file selection
            if (filePath)
            {
                app.loadSamples(filePath);
                app.scroll = 0;
                app.zoom = 1.0f;
            }
        }
        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
}

void handleViewportControls(AppContext& app) {
    ImGui::Text("Controls");
    ImGui::SliderFloat("Zoom", &app.zoom, 1.0f, 20.0f);
    ImGui::SliderInt("Scroll", &app.scroll, 0, std::max(0, (int)app.samples.size() - 100));

    ImGui::Separator();
}

void handleWaveformViewer(AppContext& app) {
    ImGui::Text("Waveform");
    if (!app.samples.empty())
    {
        int displayCount = std::max(100, (int)(app.samples.size() / app.zoom));
        int startIndex   = std::min(app.scroll, (int)app.samples.size() - displayCount);

        // "##waveform" gives a unique ID but no visible label
        ImGui::PlotLines(
            "##waveform",
            app.samples.data() + startIndex,
            displayCount,
            0,
            nullptr,
            -1.0f,
            1.0f,
            ImVec2(0, 150)
        );
    }
}