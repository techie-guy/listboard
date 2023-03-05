#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

class UI
{
private:
	void UpdateUI();

public:
	UI();
	void Init(GLFWwindow* window, const char* glsl_version);
	void Update();
	void Shutdown();

	// void Theme(ImGuiStyle& style);
};
