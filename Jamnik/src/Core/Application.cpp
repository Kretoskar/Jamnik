#include "Application.h"

#include <iostream>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"


bool Jamnik::Application::Init()
{
    _window = std::make_unique<Window>();
    if (!_window->Init())
    {
        return false;
    }
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(_window->GetGlfwWindow(), true);
    const char* glslVersion = "#version 440 core";
    ImGui_ImplOpenGL3_Init(glslVersion);

    return true;
}

void Jamnik::Application::Update()
{
    _shouldClose = glfwWindowShouldClose(_window->GetGlfwWindow());

    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags flags = 0;
    ImGui::SetNextWindowBgAlpha(0.8f);
    ImGui::Begin("chuj", nullptr, flags);
    ImGui::Text("chasdasdasdasdasddauj");

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window->GetGlfwWindow());
    glfwPollEvents();
}

void Jamnik::Application::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    _window->ShutDown();
}
