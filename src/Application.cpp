#define GLAD_GL_IMPLEMENTATION
#include "Application.h"
#include "Logger.h"

Application::Application(const int windowWidth, const int windowHeight, const char* windowTitle)
{
	AppWidth = windowWidth;
	AppHeight = windowHeight;

	loadConfig("assets/config.cfg");

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(AppWidth, AppHeight, windowTitle, NULL, NULL);
	if (window == NULL)
	{
		Logger::Error("Failed to create GLFW window");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Turn On Vsync

	// Load Glad
	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0)
	{
		Logger::Error("Failed to initialize OpenGL context");
		glfwTerminate();
	}

	// Init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::mainLoop()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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
}

void Application::loadConfig(const char* filePath)
{
	try
	{
		appConfig.readFile(filePath);
	}
	catch(const libconfig::FileIOException& fioex)
	{
		Logger::Error("Error in reading %s: [%s]", filePath, fioex.what());
		exit(EXIT_FAILURE);
	}
	catch(const libconfig::ParseException &pex)
	{
		Logger::Error("Error in parsing %s: [%s]", filePath, pex.what());
		exit(EXIT_FAILURE);
	}
}

libconfig::Setting& Application::readFromConfig()
{
	try
	{
		return appConfig.getRoot();
	}
	catch(const libconfig::SettingNotFoundException &nfex)
	{
		Logger::Error("No settings in config file");
		exit(EXIT_FAILURE);
	}
}

libconfig::Setting& Application::readFromConfig(const char* string)
{
	try
	{
		return appConfig.lookup(string);
	}
	catch(const libconfig::SettingNotFoundException &nfex)
	{
		Logger::Error("No '%s' setting in config file", string);
		exit(EXIT_FAILURE);
	}
}

void Application::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
