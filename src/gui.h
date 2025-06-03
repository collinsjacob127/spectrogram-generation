#pragma once
#include "audio.h"   // brings in AppContext definition

// Renders the window with everything
void renderMainWindow(AppContext& app);

void initializeWindow(AppContext& app);

void handleMenuBar(AppContext& app);

void handleViewportControls(AppContext& app);

void handleWaveformViewer(AppContext& app);

// void renderMainMenu(AppContext& app);
// void renderControls(AppContext& app);
// void renderWaveform(AppContext& app);
