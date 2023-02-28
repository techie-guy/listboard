# listboard

A Cross Platform Kanban Board Application written in C++ and OpenGL

## Build it
### MSYS2 Windows
1. Clone this repository recursively
2. Download MSYS2 from https://msys2.org
3. Open the UCRT64 Shell and Run `pacman -Ss mingw-w64-ucrt-x86_64-clang mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-glfw3` to install the dependencies and compiler
4. `mkdir build` and `cd build`
5. `cmake ..` to generate the build files. You can also use `COMPILE_FOR_WASM=1 cmake ..`, if you want to compile for the web using Emscripten. Note that you need to install Emscripten and set the `EMSDK_HOME="/path/to/emscripten_sdk"` environment variable
6. `ninja` to build the project
