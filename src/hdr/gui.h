#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace gui {

	bool graphicMenu = false;

	bool vsync = true;
	bool wireframe = false;
	bool fillframe = false;
	bool pointframe = false;
	bool shaderThingy = true;
	ImVec4 clear_color(0.1, 0.1, 0.1, 0.1);

	static const char* items[]{ "", "Baaaa", "Oaaaa" };
	static int selectedItem = 0;
	static bool selected[3];

	void init(GLFWwindow* window)
	{
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	}

	void draw() {
		if (vsync == true)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			static GLfloat i = 0;

			ImGui::Begin("Main");                          

			ImGui::SliderFloat("Size", &i, 0, 20); 
			glLineWidth(i);
			glPointSize(i);
			ImGui::ColorEdit3("Background\n Color", (float*)&clear_color); 

			if (ImGui::BeginMenu("Graphics Menu"))
			{
				ImGui::Checkbox("Vsync", &vsync);

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
				if (ImGui::Checkbox("Shader Model", &shaderThingy))
					if (shaderThingy == true)
						glShadeModel(GL_SMOOTH);
					else
						glShadeModel(GL_FLAT);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{
				ImGui::Button("Copy");
				ImGui::Text("Discord: https://discord.gg/P2yUtK2");
				
				ImGui::Text("Github: https://github.com/ttvtempest17/Goblin-Engine");
				ImGui::EndMenu();
			}

			static std::string previewValue = "";

			if (ImGui::BeginCombo("MultiSelectableCombo", previewValue.c_str()))
			{
				previewValue = "";
				std::vector<std::string> vec;
				for (size_t i = 0; i < IM_ARRAYSIZE(items); i++)
				{
					ImGui::Selectable(items[i], &selected[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
					if (selected[i])
					{
						vec.push_back(items[i]);
					}
				}

				for (size_t i = 0; i < vec.size(); i++)
				{
					if (vec.size() == 1)
						previewValue += vec.at(i);
					else if (!(i == vec.size()))
						previewValue += vec.at(i) + ",";
					else
						previewValue += vec.at(i);
					
				}

				ImGui::EndCombo();
			}

			ImGui::NewLine();

			ImGui::TextWrapped("Application average %.3f ms/frame \n(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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