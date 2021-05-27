 #include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include "Customs.h"
BOOL WINAPI FreeConsole(VOID);

int main()
{
    renderer instance;
    instance.OpenGL(800, 600, true);
}