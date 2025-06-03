#include "gui.h"
#include "tinyfiledialogs.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

void renderMainWindow(AppContext& app)
{
    // Window flags: show a menu bar, but allow resizing. Remove NoResize if you want it resizable.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
    
    // Start up the window
    ImGui::Begin("Waveform Viewer", nullptr, window_flags);

    // Menu Bar (File -> Select .wav file)
    if (ImGui::BeginMenuBar())
        handleMenuBar(app);

    handleViewportControls(app);

    handleWaveformViewer(app);

    ImGui::End(); // End "Waveform Viewer"
    
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