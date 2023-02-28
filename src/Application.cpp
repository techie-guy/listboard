#include "imgui.h"
#include <GLFW/glfw3.h>
#define GLAD_GLES2_IMPLEMENTATION
#include "Application.h"
#include "Logger.h"

#define IMGUI_DISABLE_FILE_FUNCTIONS

Application::Application(const int windowWidth, const int windowHeight, const char* windowTitle)
{
	AppWidth = windowWidth;
	AppHeight = windowHeight;

	Logger::Debug("Amogus %d", 69420);

	initWindow(windowTitle);
}

void Application::run()
{
	mainLoop();
	cleanup();
}

void Application::initWindow(const char* windowTitle)
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glsl_version = "#version 100";

	window = glfwCreateWindow(AppWidth, AppHeight, windowTitle, NULL, NULL);
	if (window == NULL)
	{
		Logger::Error("Failed to create GLFW window");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Turn On Vsync

	// Load Glad
#if defined(_PLATFORM_NATIVE)
	int version = gladLoadGLES2(glfwGetProcAddress);
	if (version == 0)
	{
		Logger::Error("Failed to initialize OpenGL context");
		glfwTerminate();
	}
#endif

	initImGui();
}

void Application::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Application::mainLoop()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

#if defined(__EMSCRIPTEN__)
	io.IniFilename = NULL;
	EMSCRIPTEN_MAINLOOP_BEGIN
#else
	while (!glfwWindowShouldClose(window))
#endif
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("A");
		ImGui::Text("Balls");
		ImGui::End();

		ImGui::Begin("B");
		ImGui::Text("Poop");
		ImGui::End();

		ImGui::Render();
		glViewport(0, 0, AppWidth, AppHeight);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}
#if defined(__EMSCRIPTEN__)
	EMSCRIPTEN_MAINLOOP_END;
#endif
}

void Application::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
