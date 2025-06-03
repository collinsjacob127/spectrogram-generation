/**
 * Author: Jacob Collins
 * Description:
 *  Waveform analysis program using ImGUI, dr_wav, and tinyfiledialogs.
 * Sources:
 *  There was some ChatGPT usage for getting the skeleton of this project
 *  off the ground.
 * Notes:
 *  - gui.cpp/h has code involving the setup for the GUI, windows, controls, etc.
 *  - audio.cpp/h has code involving the file selection, audio display/processing, 
 *    and most of the dedicated logic in the program.
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

        app.endFrame();
    }

    app.shutdown();
    return 0;
}
