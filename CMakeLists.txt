cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)            # Prefer GLVND when available
project(WaveformViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 and OpenGL
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories: SDL2, DrWav/tinyfiledialogs/imgui, and src/
include_directories(
    ${SDL2_INCLUDE_DIRS}
    libs
    libs/imgui
    libs/imgui/backends
    src
)

# Gather all ImGui sources (core + backends)
file(GLOB IMGUI_SRC
    libs/imgui/*.cpp
    libs/imgui/backends/imgui_impl_sdl2.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)

# Our executable consists of:
#  - src/main.cpp, src/gui.cpp, src/audio.cpp
#  - tinyfiledialogs.c
#  - all ImGui .cpp files
add_executable(waveform_viewer
    src/main.cpp
    src/gui.cpp
    src/audio.cpp
    libs/tinyfiledialogs.c
    ${IMGUI_SRC}
)

# Link against SDL2, OpenGL, GL, and GLX on Linux (or opengl32 on Windows)
target_link_libraries(waveform_viewer
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    GL        # explicit OpenGL on Linux
    GLX       # explicit GLX on Linux
)
