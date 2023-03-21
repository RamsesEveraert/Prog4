#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"
#include <vector>

namespace dae
{

    enum class GraphState
    {
        NotActivated,
        CalculationInProgress,
        CanPlot
    };

    struct Transform
    {
        float matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    class GameObject3D
    {
    public:
        Transform transform{};
        int ID{};
    };

    class GameObject3DAlt
    {
    public:
        Transform* transform{};
        int ID{};
    };

    class TrashCacheComponent : public dae::BaseComponent
    {
    public:
        TrashCacheComponent(std::weak_ptr<dae::GameObject> owner, const std::string& identifier = "");

        virtual void Update() override;
        virtual void Render() override;


    private:

        std::vector<float> m_XDataIntArray, m_XDataGameObject3D, m_XDataGameObject3DAlt, m_XDataGraphcombined;
        std::vector<float> m_YDataIntArray, m_YDataGameObject3D, m_YDataGameObject3DAlt;
        std::vector<const float*> m_YDataGraphcombined;
        int m_NumSamplesEx1;
        int m_NumSamplesEx2;
        int m_BufferSize;
        int m_MaxSteps;
       
        ImColor m_Red;
        ImColor m_Green;
        ImColor m_Bleu;
        ImU32 m_CombinedGraphColors[2];
        ImGui::PlotConfig m_ConfigIntArray;
        ImGui::PlotConfig m_ConfigGraphObjects;
        ImGui::PlotConfig m_ConfigGraphObjectsAlt;
        ImGui::PlotConfig m_ConfigCombined;

        GraphState m_Graph1State;
        GraphState m_Graph2State;
        GraphState m_Graph3State;

        void UpdateConfig();


        // ex1
        void RenderEx1();
        void CalculateEx1();
        // ex2
        void RenderEx2();
        void CalculateEx2();
        void CalculateCombined();
    };

}