#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gui.h>

#include <stdio.h>
#include <iostream>
#include <thread>



GLFWwindow* window = (GLFWwindow*)malloc(sizeof(window));
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void close_window_callback(GLFWwindow* window);
class renderer
{
public:
	void OpenGL(int SCR_WIDTH, int SCR_HEIGHT, bool hardlogging)
	{
		initlibs();
		createWin(SCR_WIDTH, SCR_HEIGHT, hardlogging);
		render();
		cleanUp();
	}

private:
	bool logger = false;
	bool done = false;

	void initlibs()
	{
		glewExperimental = true; // Needed for core profile
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

	}

	void createWin(int width, int height, bool logger)
	{

		glfwWindowHint(GLFW_SAMPLES, 4);//msaa 8x
		glfwWindowHint(GLFW_DOUBLEBUFFER, true);
		window = glfwCreateWindow(width, height, "Goblin_Engine[Dev] (default)", NULL, NULL);



		glfwMakeContextCurrent(window); // Initialize GLEW
		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
		}
		if (logger == true)
		{
			std::cout <<
				"[Goblin] Glfw Initialized. Version: " << glfwGetVersionString() << " \n" <<
				"[Goblin] Glew Initialized. Version: " << GLEW_VERSION << '\n' <<
				"[Goblin] Window pointer: 0x" << std::hex << &window << "\n";

		}

		std::cout << "[Goblin] Loaded OpenGL: " << glGetString(GL_VERSION) << '\n';
		std::cout << "[Goblin] Shader Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		glfwSetWindowSizeCallback(window, framebuffer_size_callback);

		glfwSetWindowCloseCallback(window, close_window_callback);
	}

	void render()
	{

		std::cout << "[Goblin] Renderer Thread: " << std::dec << std::this_thread::get_id() << '\n';

		gui::init(window);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(1.0f, 0.0f, 0.0f); // Red
			glVertex2f(-0.5f, -0.5f);     
			glColor3f(0.0, 0.0, 1.0);// x, y
			glVertex2f(0.5f, -0.5f);
			glColor3f(1.0, 0.0f, 0.0f);
			glVertex2f(0.5f, 0.5f);
			glColor3f(0.0, 1.0, 1.0);
			glVertex2f(-0.5f, 0.5f);
			glEnd();
			gui::draw();
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
		gui::exit();
		glfwTerminate();
		std::cout << "[Goblin] Fun programming with you. See you next time.\n";
	}

	void cleanUp()
	{
		glfwTerminate();
	}

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void close_window_callback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}