#include "Debugger.h"

#include "SceneManager.h"


using namespace dae;

Debugger::Debugger()
    : m_Scenes{ SceneManager::GetInstance().GetScenes() }
   /* , m_Io{ ImGui::GetIO() }*/
{
    
    
}

void dae::Debugger::ShowSceneInformation()
{
    if (ImGui::CollapsingHeader("Scene Information"))
    {
        if (ImGui::TreeNode("General"))
        {
            ImGui::TreePop();
        }
        
        /*ImGui::Text("ABOUT THIS DEMO:");
        ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
        ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
        ImGui::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
            "and Metrics/Debugger (general purpose Dear ImGui debugging tool).");
        ImGui::Separator();

        ImGui::Text("PROGRAMMER GUIDE:");
        ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
        ImGui::BulletText("See comments in imgui.cpp.");
        ImGui::BulletText("See example applications in the examples/ folder.");
        ImGui::BulletText("Read the FAQ at http://www.dearimgui.org/faq/");
        ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
        ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
        ImGui::Separator();

        ImGui::Text("USER GUIDE:");
        ImGui::ShowUserGuide();*/
    }
}

void dae::Debugger::ShowGlobalInformation()
{
    if (ImGui::CollapsingHeader("Global Information"))
    {
        if (ImGui::TreeNode("FPS"))
        {
           
            ImGui::TreePop();
        }
        
    }
}


void Debugger::Render()
{
        ImGui::SetNextWindowSize(ImVec2(400, 400));
        if (ImGui::Begin("Debugger"))
        {
           /* ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_Io.Framerate, m_Io.Framerate);*/
            ShowSceneInformation();
            ShowGlobalInformation();
           
        }
        ImGui::End();
}

