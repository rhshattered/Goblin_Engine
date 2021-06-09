#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gui.h>
GLFWwindow* window;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void close_window_callback(GLFWwindow* window);
namespace gl {

	void init()
	{
		GLFWwindow* window;
		if (!glfwInit())
			exit(EXIT_FAILURE);
	}

	void createWin(int width, int height)
	{
		window = glfwCreateWindow(width, height, "Goblin_Engine", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		imGL::create();

		glfwMakeContextCurrent(window);

		imGL::init(window);
		GLenum err = glewInit();

		glfwSetWindowAspectRatio(window, 16, 9);

		glfwSetWindowCloseCallback(window, close_window_callback);
		glfwSetWindowSizeCallback(window, framebuffer_size_callback);
	}

	void draw()
	{


		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			// Render a color-cube consisting of 6 quads with different colors
			
			imGL::draw(window);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	void terminate()
	{
		imGL::exit();
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void close_window_callback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}
