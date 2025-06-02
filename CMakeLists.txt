cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
project(WaveformViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# ImGui and Tiny libraries
include_directories(libs/imgui)
include_directories(libs)
file(GLOB IMGUI_SRC
    libs/imgui/*.cpp
    libs/imgui/backends/imgui_impl_sdl2.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)

# Platform specific OpenGL
if (WIN32)
    set(OPENGL_LIBRARIES opengl32)
else()
    find_package(OpenGL REQUIRED)
    set(OPENGL_LIBRARIES GL)
endif()


add_executable(waveform_viewer
    main.cpp
    libs/tinyfiledialogs.c
    ${IMGUI_SRC}
)

target_link_libraries(waveform_viewer
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

