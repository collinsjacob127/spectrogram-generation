#pragma once
#include "audio.h"   // brings in AppContext definition

// Render functions, each takes the AppContext to read samples/zoom/scroll
void renderMainMenu(AppContext& app);
void renderControls(AppContext& app);
void renderWaveform(AppContext& app);
