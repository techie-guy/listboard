#pragma once

#if defined(_PLATFORM_NATIVE)
 #include <glad/gles2.h>
#endif

#if defined(_PLATFORM_WASM)
 #define GLFW_INCLUDE_ES2

 #include <emscripten.h>
 #include <functional>
 static std::function<void()>            MainLoopForEmscriptenP;
 static void MainLoopForEmscripten()     { MainLoopForEmscriptenP(); }
 #define EMSCRIPTEN_MAINLOOP_BEGIN       MainLoopForEmscriptenP = [&]() {
 #define EMSCRIPTEN_MAINLOOP_END         }; emscripten_set_main_loop(MainLoopForEmscripten, 0, true)
#endif

#include <GLFW/glfw3.h>

#include "Logger.h"
#include "UI.h"

void RenderFrameCallback(void* arg);

class Application
{
private:
	GLFWwindow* window;

	int AppWidth;
	int AppHeight;

	UI ui;

public:
	Application();
	Application(const int windowWidth, const int windowHeight, const char* windowTitle);
	void run();

private:
	void initWindow(const char* windowTitle);
	void mainLoop();
	void cleanup();
};
