#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gui.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#include <openGL.h>

namespace render
{
	
	void GL(int width, int height)
	{
		gl::init();
		gl::createWin(width, height);
		gl::draw();
		gl::terminate();
	}

	void VK(int width, int height)
	{
		
	}
}

void select(int width, int height)
{
	GLFWwindow* window;
	if (!glfwInit())
		exit(EXIT_FAILURE);
	ImSl::create();
	glfwWindowHint(GLFW_RESIZABLE, 1);

	glfwWindowHint(GLFW_DECORATED, 0);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1); // Only on latest version
	glfwWindowHint(GLFW_AUTO_ICONIFY, 0);
	
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	window = glfwCreateWindow(width, height, "Goblin_Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	ImSl::init(window);
	GLenum err = glewInit();
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImSl::render(window);
		if (ImSl::OpenGL)
		{
			glfwTerminate();
			ImSl::exit();
			render::GL(width,height);
			

		}

		else if (ImSl::Vulkan)
		{
			render::VK(800, 600);
		}

		else if (ImSl::Directx)
		{
			
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	ImSl::exit();
	glfwDestroyWindow(window);
	glfwTerminate();

}
