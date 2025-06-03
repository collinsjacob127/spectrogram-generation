#include "gui.h"
#include "tinyfiledialogs.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

void renderMainMenu(AppContext& app)
{
    if (!ImGui::BeginMainMenuBar()) { return; }
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Select .wav file"))
        {
            // Open native file dialog
            const char* filePath = tinyfd_openFileDialog(
                "Open WAV File", 
                "../wav-files/",            // start in wav files dir
                0, NULL, NULL, 
                0
            );
            if (filePath) { app.loadSamples(filePath); }
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

void renderControls(AppContext& app)
{
    ImGui::Begin("Controls");
    // Zoom slider (visible label)
    ImGui::SliderFloat("Zoom", &app.zoom, 1.0f, 20.0f);
    // Scroll slider (visible label)
    ImGui::SliderInt("Scroll", &app.scroll, 0, std::max(0, (int)app.samples.size() - 100));
    ImGui::End();
}

void renderWaveform(AppContext& app)
{
    ImGui::Begin("Waveform");
    if (!app.samples.empty())
    {
        int displayCount = std::max(100, (int)(app.samples.size() / app.zoom));
        int startIndex   = std::min(app.scroll, (int)app.samples.size() - displayCount);

        ImGui::Text("Waveform");
        // Use "##waveform" as ID so no visible label but unique ImGui ID
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
    ImGui::End();
}
