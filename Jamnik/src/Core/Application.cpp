#include "Application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

bool Application::Start()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _window = glfwCreateWindow(1920, 1080, "Jamnik", NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(320, 0, 1280, 720);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    const char* glslVersion = "#version 440 core";
    ImGui_ImplOpenGL3_Init(glslVersion);

    glClearColor(0.15f, 0.5f, 1.0f, 1.0f);

    return true;
}

void Application::Update()
{
    _shouldClose = glfwWindowShouldClose(_window);

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

    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void Application::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}
