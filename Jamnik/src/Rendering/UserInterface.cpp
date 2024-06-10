#include "UserInterface.h"

#include "Core/Logger.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool UserInterface::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glslVersion = "#version 440 core";
    ImGui_ImplOpenGL3_Init(glslVersion);

    return true;
}

void UserInterface::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (Jamnik::Logger::loggedLineBufferCurrCount > 0)
    {
        ImGuiWindowFlags flags = 0;
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::Begin("Console", nullptr, flags);
        
        for (unsigned int i = 0; i < Jamnik::Logger::loggedLineBufferCurrCount; i++)
        {
            switch (Jamnik::Logger::logLinesVerbosity[i]) {
            case Jamnik::Error:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                break;
            case Jamnik::Warning:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
                break;
            case Jamnik::Message:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                break;
                //TODO: Add checknoentry
            }
        
            ImGui::Text(Jamnik::Logger::logLines[i].c_str());
            
            ImGui::PopStyleColor();
        }

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(0.0f);
        }
        
        ImGui::End();
    }

    ImGuiWindowFlags flags = 0;
    ImGui::Begin("Camera", nullptr, flags);

    if (cameraSpeed)
    {
        ImGui::SliderFloat("Speed", cameraSpeed, 0.01f, 0.2f);
        ImGui::SliderFloat("Sensitivity", cameraSensitivity, 10, 200);
    }
    
    ImGui::End();
}

void UserInterface::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::RegisterCameraSpeedVarPtr(float* speed)
{
    cameraSpeed = speed;
}

void UserInterface::RegisterCameraSensitivityVarPtr(float* sensitivity)
{
    cameraSensitivity = sensitivity;
}
