#include "TrashCacheComponent.h"

#include "imgui.h"

#include <chrono>
#include <algorithm>
#include <numeric> 


dae::TrashCacheComponent::TrashCacheComponent(std::weak_ptr<dae::GameObject> owner, const std::string& identifier)
    : BaseComponent(owner, identifier)
    , m_NumSamples{20}
    , m_BufferSize{10'000'000}
    , m_CanCalcEx1{ false }
    , m_IsCalculatingEx1{ false }
    , m_CanPlotEx1{ false }
{
    ImU32 graphColor{ ImColor(217, 132, 69) };

    m_PlotConfigEx1.values.color = graphColor;
    m_PlotConfigEx1.tooltip.show = false;
    m_PlotConfigEx1.tooltip.format = "x%.2f, y=%.2f";
    m_PlotConfigEx1.grid_y.show = true;
    m_PlotConfigEx1.grid_y.size = 5.f;
    m_PlotConfigEx1.grid_y.subticks = 1;
    m_PlotConfigEx1.frame_size = ImVec2(200, 150);
    m_PlotConfigEx1.line_thickness = 1.f;
}

void dae::TrashCacheComponent::Update()
{
    if (m_CanCalcEx1)
    {
        CalculateEx1();
        UpdateConfigEx1();
    }

}

void dae::TrashCacheComponent::Render()
{
    RenderEx1();
}

void dae::TrashCacheComponent::RenderEx1()
{
    ImGui::SetNextWindowSize(ImVec2(250, 300));
    ImGui::Begin("Exercice 1");

    if (ImGui::Button("-"))
    {
        m_NumSamples--;

        // 3 samples is minimum otherwise it crashes because it removesthe highest and lowest value

        if (m_NumSamples < 3)
            m_NumSamples = 3;
    }

    ImGui::SameLine();

    if (ImGui::Button("+"))
    {
        m_NumSamples++;
        if (m_NumSamples > 30) 
            m_NumSamples = 30;
    }

    ImGui::SameLine();

    ImGui::PushItemWidth(100);

    

    ImGui::SliderInt("# samples", &m_NumSamples, 3, 30);

    if (m_IsCalculatingEx1)
    {
        ImGui::Text("Wait for it...");
    }
    else
    {
        if (ImGui::Button("Trash the cache!"))
            m_CanCalcEx1 = true;
    }

    if (m_CanPlotEx1)
        ImGui::Plot("Exercice 1", m_PlotConfigEx1);

    ImGui::End();
}

void dae::TrashCacheComponent::UpdateConfigEx1()
{
    m_PlotConfigEx1.values.xs = m_XAxisValues.data(); // stepsizes
    m_PlotConfigEx1.values.ys = m_YAxisValues.data(); // average time samples
    m_PlotConfigEx1.values.count = static_cast<int>(m_XAxisValues.size());
    m_PlotConfigEx1.scale.min = 0;

    const auto maxElement{ std::max_element(m_YAxisValues.begin(), m_YAxisValues.end()) };

    maxElement == m_YAxisValues.end() ? m_PlotConfigEx1.scale.max = 0
                                      : m_PlotConfigEx1.scale.max = *maxElement;

    m_IsCalculatingEx1 = false;
    m_CanCalcEx1 = false;
    m_CanPlotEx1 = true;
}


void dae::TrashCacheComponent::CalculateEx1()
{
    m_IsCalculatingEx1 = true;

    // reset X and Yaxes
    m_XAxisValues.clear();
    m_YAxisValues.clear();

    // Parameters for Calculation
    int* pBuffer{ new int[m_BufferSize] {} };
    int maxSteps{ 1024 };

    // Parameters for ImGui
    m_XAxisValues.reserve(m_NumSamples);
    m_YAxisValues.reserve(m_NumSamples);
       

        for (int stepsize{ 1 }; stepsize <= maxSteps; stepsize *= 2)
        {
            
            m_XAxisValues.push_back(static_cast<float>(stepsize));

            std::vector<float> samples;
            samples.reserve(m_NumSamples);

            for (int sample{ 0 }; sample < m_NumSamples; ++sample)
            {
                auto start = std::chrono::high_resolution_clock::now();

                for (int i = 0; i < m_BufferSize; i += stepsize)
                {
                    pBuffer[i] *= 2;
                }

                auto end = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                samples.push_back(static_cast<float>(elapsedTime));
            }

            // Remove the highest and lowest value 
            std::sort(samples.begin(), samples.end());
            samples.erase(samples.begin());
            samples.pop_back();

            float averageElapsedTime = std::accumulate(samples.begin(), samples.end(), 0.0f) / samples.size();
            m_YAxisValues.push_back(averageElapsedTime);
        }
        m_IsCalculatingEx1 = false;
    delete[] pBuffer;
}


