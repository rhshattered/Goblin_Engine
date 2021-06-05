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
		imGL::create();
	}

	void createWin(int width, int height)
	{
		window = glfwCreateWindow(width, height, "Goblin_Engine", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);

		imGL::init(window);
		GLenum err = glewInit();

		glfwSetWindowAspectRatio(window, 16, 9);

	}

	void draw()
	{


		while (!glfwWindowShouldClose(window))
		{
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;
			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glRotatef((float)glfwGetTime() * 50.f, 10.f, 10.f, 10.f);
			glBegin(GL_QUADS);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.5f, -0.5, 0.f);

			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(-0.5f, 0.5, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.5f, 0.5, 0.f);

			glVertex3f(0.5f, -0.5f, 0.0f);

			glEnd();
			imGL::draw(window);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	void terminate()
	{
		imGL::exit();
		glfwDestroyWindow(window);
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
