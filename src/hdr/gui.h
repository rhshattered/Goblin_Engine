#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

static void mouse_button_callback(GLFWwindow* window, int button, int action,
	int mods);

static double cursor_pos_x = 0;
static double cursor_pos_y = 0;
static double delta_x = 0;
static double delta_y = 0;

static int window_drag_active = 0;

namespace imGL {
	
	void guiLogic();

	bool graphicMenu = false;
	bool vsync = true, vsync2 = false;
	bool wireframe = false;
	bool fillframe = false;
	bool pointframe = false;
	bool shaderThingy = true;
	bool rotate = true;
	bool fourbyThree = false;
	bool defaultAs = true;
	bool darkMode = true;
	bool lightMode = false;
	bool classicMode = false;
	bool fpsActive = false;
	bool metricsWin = false;
	bool zBuffer = true;
	ImVec4 clear_color(0.1, 0.1, 0.1, 0.1);
	int dropDown = 0;
	const char* ddChar[2] = { "Wireframe", "Vertex" };
	ImGuiContext* ctx;
	void create()
	{
		IMGUI_CHECKVERSION();
		ctx = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
	}

	void init(GLFWwindow* window)
	{
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
		
	}

	void draw(GLFWwindow* window) {
		glfwMakeContextCurrent(window);
		ImGui::SetCurrentContext(ctx);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			guiLogic();

			static GLfloat i = 0;

			float ratio;
			int width, height;

			ImGui::Begin("Main");

			glLineWidth(i);
			glPointSize(i);

			if (ImGui::BeginMenu("UI Settings"))
			{
				if (ImGui::BeginMenu("Colors"))
				{
					ImGui::Text("Background Color");
					ImGui::ColorEdit3("", (float*)&clear_color);

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Theme"))
				{
					if (ImGui::Checkbox("Dark Mode", &darkMode))
					{
						if (darkMode == true)
							ImGui::StyleColorsDark();
						classicMode = false;
						lightMode = false;
					}

					if (ImGui::Checkbox("Classic", &classicMode))
					{
						if (classicMode == true)
							ImGui::StyleColorsClassic();
						darkMode = false;
						lightMode = false;
					}

					if (ImGui::Checkbox("Flash Bang", &lightMode))
					{

						if (lightMode == true)
							ImGui::StyleColorsLight();
						
						darkMode = false;
						classicMode = false;
						if (ImGui::IsItemHovered())
						{
							ImGui::BeginTooltip();
							ImGui::Text("Lightmode for the people that enjoy burning their eyes.");
							ImGui::EndTooltip();
						}
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Display Menu"))
			{
				if (ImGui::BeginMenu("Vsync"))
				{
					if (ImGui::Checkbox("1 Frame", &vsync))
						vsync2 = false;

					if (ImGui::Checkbox("2 Frame", &vsync2))
						vsync = false;

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Aspect Ratio"))
				{
					if (ImGui::Checkbox("4:3", &fourbyThree))
					{
						if (fourbyThree == true)
						{
							defaultAs = false;
							glfwSetWindowAspectRatio(window, 4, 3);
						}

					}

					if (ImGui::Checkbox("16:9", &defaultAs))
						if (defaultAs == true)
						{
							fourbyThree = false;
							glfwSetWindowAspectRatio(window, 16, 9);
						}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Rendering"))
			{
				ImGui::SliderFloat("Size", &i, 0, 20);
				if (ImGui::Checkbox("WireFrame", &wireframe))
					if (wireframe == true) {
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						pointframe = false;
					}

					else {
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					}

				if (ImGui::Checkbox("PointFrame", &pointframe))
					if (pointframe == true) {
						glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
						wireframe = false;
					}
					else {
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					}
				
				if (ImGui::Checkbox("ZBuffer", &zBuffer))
				{
					if (zBuffer == true)
						glCullFace(GL_TRUE);
					else if (zBuffer == false)
						glCullFace(GL_FALSE);
				}
				ImGui::EndMenu();
			}
				

			if (ImGui::BeginMenu("Version"))
			{
				ImGui::Text("ImGui: %s", IMGUI_VERSION);
				ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
				ImGui::Text("Glfw: %s", glfwGetVersionString());
				ImGui::Text("Glew: %s", glewGetString(GLEW_VERSION));

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Profilers"))
			{
				if (ImGui::Button("FPS"))
					fpsActive = !fpsActive;
				if (ImGui::Checkbox("Metrics Window", &metricsWin))
					metricsWin = !metricsWin;
					
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Links"))
			{
				if (ImGui::Button("Discord"))
				{
					ImGui::BeginTooltip();
					ImGui::SetClipboardText("https://discord.gg/P2yUtK2");
					ImGui::EndTooltip();
				}

				if (ImGui::Button("Github"))
				{
					ImGui::BeginTooltip();
					ImGui::SetClipboardText("https://github.com/ttvtempest17/Goblin_Engine");
					ImGui::EndTooltip();
				}
				ImGui::EndMenu();
			}

			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void exit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void guiLogic()
	{
		if (vsync == true)
			glfwSwapInterval(1);
		else if (vsync2 == true)
			glfwSwapInterval(2);
		else
			glfwSwapInterval(0);

		if (fpsActive)
		{
			ImGui::Begin("FPS");
			ImGui::Text("%.3f ms/frame \n(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}
}


namespace ImVK
{

}

namespace ImDx
{

}

namespace ImSl
{
	bool OpenGL = false;
	bool Directx = false;
	bool Vulkan = false;
	int choice = 0;
	ImGuiContext *startup;
	ImVec2 pos;
	ImVec2 size;
	ImVec2 glfwSize = {0, 0};
	ImVec2 mousePos;
	int winPosx = 0, winPosy = 0;
	int glSizex = 0, glSizey = 0;
	int winx = 0, winy = 0;

	bool reposition = false;

	bool sizeMenu = false;
	void create()
	{
		IMGUI_CHECKVERSION();
		startup = ImGui::CreateContext();
		ImGui::SetCurrentContext(startup);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
	}

	void init(GLFWwindow* window)
	{
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
		ImGui::SetCurrentContext(startup);
		
		ImGui::StyleColorsClassic();
	
	}

	void render(GLFWwindow* window)
	{
		//mouseposcallback(window);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Launcher", 0, 
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_NoScrollWithMouse);
			if (ImGui::IsItemHovered())
			{
				reposition = true;
				if (window_drag_active) {
					ImVec2 mouseD = ImGui::GetMousePos();
					delta_x = mouseD.x - cursor_pos_x;
					delta_y = mouseD.y - cursor_pos_y;

					int x, y;
					glfwGetWindowPos(window, &x, &y);
					glfwSetWindowPos(window, x + delta_x, y + delta_y);
				}
			}

			else
				reposition = false;
			glSizex = glfwSize.x;
			glSizey = glfwSize.y;
			ImGuiStyle& style = ImGui::GetStyle();
			style.AntiAliasedLines = true;
			style.AntiAliasedFill = true;
			size = ImGui::GetWindowSize();
			pos = ImGui::GetWindowPos();
			glfwGetWindowPos(window, &glSizex, &glSizey);
				if (ImGui::Button("OpenGL"))
				{
					OpenGL = !OpenGL;
				}

				if (ImGui::Button("Vulkan"))
				{
					Vulkan = !Vulkan;
				}

				if (ImGui::Button("DirectX"))
				{
					Directx = !Directx;
				}

				if (ImGui::BeginMenu("Window Position"))
				{	
					if (ImGui::Button("Reset"))
						ImGui::SetWindowPos(ImVec2(0, 0));
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Window Data"))
				{
					if (ImGui::BeginMenu("ImGui Size"))
					{
							ImGui::Text("ImGui SizeX: %f", size.x);
							ImGui::Text("ImGui SizeY: %f", size.y);
						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("ImGui Position"))
					{
						ImGui::Text("ImGui PosX: %f", pos.x);
						ImGui::Text("ImGui PosY: %f", pos.y);
						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Win Position"))
					{
						ImGui::Text("Glfw PosY: %i", glSizex);
						ImGui::Text("Glfw PosX: %i", glSizey);
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}

				glfwSetWindowSize(window, size.x, size.y);
				if (reposition)
					ImGui::Text("Repositionable");
				else
					ImGui::Text("Non Repositionable");
				ImGui::End();

			ImGui::EndFrame();

		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	}

	void exit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(startup);
	}



}

static void mouse_button_callback(GLFWwindow* window, int button, int action,
	int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		window_drag_active = 1;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		cursor_pos_x = floor(x);
		cursor_pos_y = floor(y);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		window_drag_active = 0;
	}
}