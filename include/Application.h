#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <libconfig.h++>

#include "Logger.h"


class Application
{
private:
	GLFWwindow* window;
	int AppWidth;
	int AppHeight;

	libconfig::Config appConfig;

public:
	Application();
	Application(const int windowWidth, const int windowHeight, const char* windowTitle);
	void run();

private:
	void initWindow(const char* windowTitle);
	void mainLoop();
	void cleanup();

	void loadConfig(const char* filePath);
	libconfig::Setting& readFromConfig();
	libconfig::Setting& readFromConfig(const char* string);
};
