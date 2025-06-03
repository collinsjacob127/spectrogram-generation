/**
 * Author: Jacob Collins
 * Description:
 *  Waveform analysis program using ImGUI, dr_wav, and tinyfiledialogs.
 * Sources:
 *  There was some ChatGPT usage for getting the skeleton of this project
 *  off the ground.
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
        renderMainWindow(app);
        // renderMainMenu(app);
        // renderControls(app);
        // renderWaveform(app);

        app.endFrame();
    }

    app.shutdown();
    return 0;
}
