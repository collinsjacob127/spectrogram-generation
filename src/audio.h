#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>

// Forward‐declare dr_wav types (the implementation is in audio.cpp)
#include "dr_wav.h"

// Application context that holds state & wraps SDL/ImGui init + cleanup
struct AppContext {
    std::vector<float> samples;   // mono samples (normalized)
    float zoom  = 1.0f;           // how “zoomed in” the waveform is
    int   scroll = 0;             // index offset into samples[]
    bool  quit   = false;

    SDL_Window*    window     = nullptr;
    SDL_GLContext  gl_context = nullptr;

    // Initialize SDL, create window & GL context, setup ImGui
    bool init();
    // Shutdown ImGui + SDL, free resources
    void shutdown();

    // Poll SDL events & feed them into ImGui
    void handleEvents();
    // Begin a new ImGui frame
    void beginFrame();
    // Render ImGui and swap buffers
    void endFrame();

    bool shouldQuit() const { return quit; }

    // Load WAV from disk, convert to mono float samples
    void loadSamples(const char* path);
};
