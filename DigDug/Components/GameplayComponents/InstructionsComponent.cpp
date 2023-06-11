#include "InstructionsComponent.h"
#include "imgui.h"

void dae::InstructionsComponent::RenderImGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 15));
    if (m_ShowInstructionsWindow)
    {
        if (ImGui::Begin("Instructions", &m_ShowInstructionsWindow, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("warning:\n");
            ImGui::Text("level loading works but the button (N-key) \n");
            ImGui::Text("works only once, I couldn't fix the crash \n");
            ImGui::Text("in time  \n");
            ImGui::Text("I couldn't finish the game because \n");
            ImGui::Text("i got stuck and couldn't fix it to continue\n");
            ImGui::Text("\n");
            ImGui::Text("WASD-keys to move and joystick");
          
        }
        

        ImGui::End();
    }
}
