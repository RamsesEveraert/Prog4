#include "InstructionsComponent.h"
#include "imgui.h"

void dae::InstructionsComponent::RenderImGui()
{
    ImGui::SetNextWindowPos(ImVec2(300, 15));
    if (ImGui::Begin("Input Instructions", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::BeginTabBar("Exercises"))
        {
            if (ImGui::BeginTabItem("Player 1 (controller)"))
            {
                ImGui::Text("B-button: Increase score with 100 points");
                ImGui::Text("A-button: Decrease Lives with 1");
                ImGui::Text("X-button: Decrease score with 100 points");
                ImGui::Text("Y-button: Increase Lives with 1");
                ImGui::Text("LeftThumbstick: Move");
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Player 2 (keyboard)"))
            {
                ImGui::Text("Arrow-Key-Up: Increase Lives with 1");
                ImGui::Text("Arrow-Key-Right: Increase score with 100 points");
                ImGui::Text("Arrow-Key-Down: Decrease Lives with 1");
                ImGui::Text("Arrow-Key-Left: Decrease score with 100 points");
                ImGui::Text("Z-key: Move Up");
                ImGui::Text("D-key: Move Right");
                ImGui::Text("S-key: Move Down");
                ImGui::Text("Q-key: Left");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }       
    }
    ImGui::End();
}
