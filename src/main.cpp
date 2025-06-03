/**
 * Author: Jacob Collins
 * Description:
 *  Waveform analysis program using ImGUI, dr_wav, and tinyfiledialogs.
 */
#include "gui.h"
#include "audio.h"

int main(int, char**)
{
    AppContext app;
    if (!app.init())
        return -1;

    // Main loop
    while (!app.shouldQuit())
    {
        app.handleEvents();
        app.beginFrame();

        // Render the top menu + controls + waveform
        renderMainMenu(app);
        renderControls(app);
        renderWaveform(app);

        app.endFrame();
    }

    app.shutdown();
    return 0;
}
