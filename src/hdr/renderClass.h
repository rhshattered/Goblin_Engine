#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <thread>

#include <openGL.h>

void rendererGL(int width, int height)
{
	gl::init();
	gl::createWin(width, height);
	gl::draw();
	gl::terminate();
}


