#define GLAD_GLES2_IMPLEMENTATION
#include "Application.h"
#include "Logger.h"

Application::Application(const int windowWidth, const int windowHeight, const char* windowTitle)
{
	AppWidth = windowWidth;
	AppHeight = windowHeight;

	initWindow(windowTitle);
	ui.Init(window, "#version 100");
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
}

void Application::mainLoop()
{
	ImGuiIO& io = ImGui::GetIO();

#if defined(__EMSCRIPTEN__)
	io.IniFilename = NULL;
	EMSCRIPTEN_MAINLOOP_BEGIN
#else
	while (!glfwWindowShouldClose(window))
#endif
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glViewport(0, 0, AppWidth, AppHeight);

		ui.Update();

		glfwSwapBuffers(window);
	}
#if defined(__EMSCRIPTEN__)
	EMSCRIPTEN_MAINLOOP_END;
#endif
}

void Application::cleanup()
{
	ui.Shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();
}
