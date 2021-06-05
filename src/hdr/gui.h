#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace imGL {

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
	bool fpsActive = false;
	ImVec4 clear_color(0.1, 0.1, 0.1, 0.1);
	int dropDown = 0;

	const char* ddChar[2] = { "Wireframe", "Vertex" };

	void create()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
	}

	void init(GLFWwindow* window)
	{
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	}

	void draw(GLFWwindow* window) {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			static GLfloat i = 0;

			float ratio;
			int width, height;

			if (fpsActive)
			{
				ImGui::Begin("FPS");
				ImGui::Text("%.3f ms/frame \n(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			ImGui::Begin("Main");
			if (vsync == true)
				glfwSwapInterval(1);
			else if (vsync2 == true)
				glfwSwapInterval(2);
			else
				glfwSwapInterval(0);
			glLineWidth(i);
			glPointSize(i);

			if (ImGui::BeginMenu("UI Theme"))
			{
				ImGui::ColorEdit3("Background\n Color", (float*)&clear_color);

				if (ImGui::Checkbox("Dark Mode", &darkMode))
				{
					if (darkMode == true)
						ImGui::StyleColorsDark();
					lightMode = false;
				}

				if (ImGui::Checkbox("Flash Bang", &lightMode))
				{

					if (lightMode == true)
						ImGui::StyleColorsLight();
					darkMode = false;
					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Lightmode for the people that enjoy burning their eyes.");
						ImGui::EndTooltip();
					}
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

}


namespace ImVK
{

}

namespace ImDx
{

}