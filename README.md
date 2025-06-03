# Spectrogram Generation

This project is used to generate and analyze spectrograms and waveforms from .wav files, similar to [Raven](https://www.birds.cornell.edu/ccb/raven-pro/).

## Feature Progress

- [x] OpenGL + ImGUI Window Setup
- [x] File selection + loading
- [x] Waveform display
  - [x] Viewport zoom + scroll
- [ ] Spectrogram Generation
  - [ ] Spectrogram View
  - [ ] Spectrogram selection
  - [ ] Spectrogram Annotation
- [ ] File output
- [ ] No GUI Mode

## Setup

Clone the repo:

```
git clone --recurse-submodules git@github.com:collinsjacob127/spectrogram-generation.git
```

### Ubuntu 22.04+ or WSL2:

Install requirements:

```
sudo apt update
sudo apt install build-essential cmake libsdl2-dev libgl1-mesa-dev
```

Build project:

```
# Navigate to project directory
cd spectrogram-generation

# Create and enter build directory
mkdir build
cd build

# Run CMake and build
cmake ..
make

# Run the application
./waveform_viewer
```

### Windows (MSYS2 Recommended)

Install MSYS2 (https://www.msys2.org/)

Inside MSYS2 MinGW64 shell:
```
pacman -Syu
# After prompted restart, reopen the shell and continue:
pacman -Syu

# Install development tools and libraries
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-SDL2 mingw-w64-x86_64-opengl
```

Build project:

```
# Navigate to project folder
cd /c/your/path/to/spectrogram-generation

# Create build directory and compile
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make

# Run
./waveform_viewer.exe
```

