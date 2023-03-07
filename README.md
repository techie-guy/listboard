# listboard

A Simple and Cross Platform Kanban Board Application written in C++ and OpenGL ES

### Fonts in `assets` from https://nerdfonts.com

## Build it
First of all clone this repo recusively using `git clone --recursive https://github.com/techie-guy/listboard.git` and `cd` to it

### MSYS2 Windows
1. Download MSYS2 from https://msys2.org. Follow the instructions on their page on how to download, install and use MSYS2.
2. Open the UCRT64 Shell and Run `pacman -Ss mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-glfw3` to install the dependencies and a compiler (GCC or Clang).
3. `cd` to the project directory and run `mkdir build && cd build`
4. `cmake ..` to generate the build files.
5. Finally, run `ninja` to build the project.

### Emscripten
1. Download Emscripten from https://emscripten.org/docs/getting_started/downloads.html. Follow the instructions on their page on how to download, install and activate Emscripten SDK.
2. After you have downloaded the SDK and it is active in your environment, Use `emcc --version` to verify.
3. Run `mkdir web-build` and `cd web-build`
4. Then, run `cmake .. -DPLATFORM=Emscripten -DCMAKE_TOOLCHAIN_FILE=path/to/emscripten_sdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake`
5. Finally, run `ninja` to build the project.

### Linux
**Installing Dependencies**

**Debian and Derivatives**
* For X11: `apt install build-essential cmake git libglfw3 libglfw3-dev`
* For Wayland: `apt install build-essential cmake git libglfw3-wayland libglfw3-dev`

**Arch and Derivatives**
* For X11: `pacman -S build-essential cmake git glfw-x11`
* For Wayland: `pacman -S build-essential cmake git glfw-wayland`

**Building the Project**
1. `cd` to the project directory and run `mkdir build && cd build`
2. `cmake ..` to generate the build files.
3. Finally, run `make` to build the project.
