#include "DebugComponent.h"
#include "GameObject.h"
#include "Timer.h"

#include <stdio.h>

dae::DebugComponent::DebugComponent()
    : m_Io {ImGui::GetIO()}
{
    m_NameGameObject = GetOwner()->GetObjectName();
   
}

void dae::DebugComponent::Render()
{
    ImGui::SetNextWindowSize(ImVec2(400, 400));
    if (ImGui::Begin(("GameObject: " + m_NameGameObject).c_str()))
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_Io.Framerate, m_Io.Framerate);

        if (ImGui::BeginTabBar("Information"))
        {
            if (ImGui::BeginTabItem("Information GameObject"))
            {
                GameObjectInformation();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Information Inputs"))
            {
                //TODO 
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}

void dae::DebugComponent::GameObjectInformation()
{
}


