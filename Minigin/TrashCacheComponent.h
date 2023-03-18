#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"
#include <vector>

namespace dae
{
    class TrashCacheComponent : public dae::BaseComponent
    {
    public:
        TrashCacheComponent(std::weak_ptr<dae::GameObject> owner, const std::string& identifier = "");

        virtual void Update() override;
        virtual void Render() override;


    private:
        int m_NumSamples;
        const int m_BufferSize;

        bool m_CanCalcEx1, m_IsCalculatingEx1, m_CanPlotEx1;

        ImGui::PlotConfig m_PlotConfigEx1{};

        std::vector<float> m_YAxisValues;
        std::vector<float> m_XAxisValues;

        void RenderEx1();
        void CalculateEx1();

        void UpdateConfigEx1();
    };

}
