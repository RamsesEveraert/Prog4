#include "TrashCacheComponent.h"

#include "imgui.h"

#include <chrono>
#include <algorithm>
#include <numeric> 


dae::TrashCacheComponent::TrashCacheComponent(std::weak_ptr<dae::GameObject> owner, const std::string& identifier)
    : BaseComponent(owner, identifier)
    , m_NumSamplesEx1{ 20 }
    , m_NumSamplesEx2{ 20 }
    , m_BufferSize{ 10000000 }
    , m_MaxSteps{ 1024 }
    , m_Red{ ImColor(255, 0, 0) }
    , m_Green{ ImColor(0, 255, 0) }
    , m_Bleu{ ImColor(0, 0, 255) }
    , m_CombinedGraphColors {m_Green, m_Bleu}
    , m_Graph1State{ GraphState::NotActivated }
    , m_Graph2State{ GraphState::NotActivated }
    , m_Graph3State{ GraphState::NotActivated }
{

    // Parameters for ImGui
    m_XDataIntArray.reserve(m_NumSamplesEx1);
    m_YDataIntArray.reserve(m_NumSamplesEx1);
    m_XDataGameObject3D.reserve(m_NumSamplesEx1);
    m_YDataGameObject3D.reserve(m_NumSamplesEx1);
    m_XDataGameObject3DAlt.reserve(m_NumSamplesEx1);
    m_YDataGameObject3DAlt.reserve(m_NumSamplesEx1);

    // Parameters graph
    m_ConfigIntArray.values.color = m_Red;
    m_ConfigIntArray.tooltip.show = false;
    m_ConfigIntArray.tooltip.format = "x%.2f, y=%.2f";
    m_ConfigIntArray.grid_y.show = true;
    m_ConfigIntArray.grid_y.size = 5.f;
    m_ConfigIntArray.grid_y.subticks = 1;
    m_ConfigIntArray.frame_size = ImVec2(200, 150);
    m_ConfigIntArray.line_thickness = 1.f;

    m_ConfigGraphObjects = m_ConfigIntArray;
    m_ConfigGraphObjects.values.color = m_Green;
    m_ConfigGraphObjects.frame_size = ImVec2(150, 100);

    m_ConfigGraphObjectsAlt = m_ConfigIntArray;
    m_ConfigGraphObjectsAlt.values.color = m_Bleu;
    m_ConfigGraphObjectsAlt.frame_size = ImVec2(150, 100);

    m_ConfigCombined = m_ConfigIntArray;
    m_ConfigCombined.values.colors = m_CombinedGraphColors;
    m_ConfigCombined.frame_size = ImVec2(150, 100);
    m_ConfigCombined.values.ys_count = 2;
}

void dae::TrashCacheComponent::Update()
{
    if (m_NumSamplesEx1 < 3) m_NumSamplesEx1 = 3;
    if (m_NumSamplesEx2 < 3) m_NumSamplesEx2 = 3;

    if (m_Graph1State == GraphState::CalculationInProgress)
    {
        CalculateEx1();
        UpdateConfig();
    }
    else if (m_Graph2State == GraphState::CalculationInProgress || m_Graph3State == GraphState::CalculationInProgress)
    {
        CalculateEx2();
        UpdateConfig();
    }

}

void dae::TrashCacheComponent::Render()
{
    ImGui::SetNextWindowSize(ImVec2(400, 400));
    ImGui::SetNextWindowPos(ImVec2(50, 50));

    if (ImGui::Begin("Trash the cache!"))
    {
        if (ImGui::BeginTabBar("Exercises"))
        {
            if (ImGui::BeginTabItem("Exercise 1"))
            {
                RenderEx1();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Exercise 2"))
            {
                RenderEx2();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}

void dae::TrashCacheComponent::RenderEx1()
{

    ImGui::PushItemWidth(275.f);
    ImGui::InputInt("#Sample", &m_NumSamplesEx1, 1, 100);
    ImGui::PopItemWidth();

    if (ImGui::Button("Trash the cache!"))
    {
        m_Graph1State = GraphState::CalculationInProgress;
        ImGui::Text("Wait for it...");
    }

    if (m_Graph1State == GraphState::CanPlot) ImGui::Plot("Exercice 1", m_ConfigIntArray);


}

void dae::TrashCacheComponent::RenderEx2()
{

    ImGui::PushItemWidth(275.f);
    ImGui::InputInt("# Sample", &m_NumSamplesEx1, 1, 100);
    ImGui::PopItemWidth();

    // graph 2

    if (m_Graph2State == GraphState::NotActivated or m_Graph2State == GraphState::CanPlot)
    {
        if (ImGui::Button("Trash the cache with GameObject3D!"))
        {
            m_Graph2State = GraphState::CalculationInProgress;
            ImGui::Text("Wait for it...");
        }

        if (m_Graph2State == GraphState::CanPlot) ImGui::Plot("Object3D", m_ConfigGraphObjects);

    }

    // graph 3

    if (m_Graph3State == GraphState::NotActivated or m_Graph3State == GraphState::CanPlot)
    {
        if (ImGui::Button("Trash the cache with GameObject3DAlt!"))
        {
            m_Graph3State = GraphState::CalculationInProgress;
            ImGui::Text("Wait for it...");
        }

        if (m_Graph3State == GraphState::CanPlot) ImGui::Plot("Object3D", m_ConfigGraphObjectsAlt);

    }

    if (m_Graph2State == GraphState::CanPlot and m_Graph3State == GraphState::CanPlot)
    {
        ImGui::Text("Combined:");
        CalculateCombined();

    }

    ImGui::End();

}

void dae::TrashCacheComponent::UpdateConfig()
{


    if (m_Graph1State == GraphState::CalculationInProgress)
    {
        m_ConfigIntArray.values.xs = m_XDataIntArray.data(); // stepsizes
        m_ConfigIntArray.values.ys = m_YDataIntArray.data(); // average time samples
        m_ConfigIntArray.values.count = static_cast<int>(m_XDataIntArray.size());
        m_ConfigIntArray.scale.min = 0;

        const auto maxElement{ std::max_element(m_YDataIntArray.begin(), m_YDataIntArray.end()) };

        maxElement == m_YDataIntArray.end() ? m_ConfigIntArray.scale.max = 0
            : m_ConfigIntArray.scale.max = *maxElement;

        m_Graph1State = GraphState::CanPlot;
    }

    if (m_Graph2State == GraphState::CalculationInProgress)
    {
        m_ConfigGraphObjects.values.xs = m_XDataGameObject3D.data(); // stepsizes
        m_ConfigGraphObjects.values.ys = m_YDataGameObject3D.data(); // average time samples
        m_ConfigGraphObjects.values.count = static_cast<int>(m_XDataGameObject3D.size());
        m_ConfigGraphObjects.scale.min = 0;

        const auto maxElement{ std::max_element(m_YDataGameObject3D.begin(), m_YDataGameObject3D.end()) };

        maxElement == m_YDataGameObject3D.end() ? m_ConfigGraphObjects.scale.max = 0
            : m_ConfigGraphObjects.scale.max = *maxElement;

        m_Graph2State = GraphState::CanPlot;
    }

    if (m_Graph3State == GraphState::CalculationInProgress)
    {
        m_ConfigGraphObjectsAlt.values.xs = m_XDataGameObject3DAlt.data(); // stepsizes
        m_ConfigGraphObjectsAlt.values.ys = m_YDataGameObject3DAlt.data(); // average time samples
        m_ConfigGraphObjectsAlt.values.count = static_cast<int>(m_XDataGameObject3DAlt.size());
        m_ConfigGraphObjectsAlt.scale.min = 0;

        const auto maxElement{ std::max_element(m_YDataGameObject3DAlt.begin(), m_YDataGameObject3DAlt.end()) };

        maxElement == m_YDataGameObject3DAlt.end() ? m_ConfigGraphObjectsAlt.scale.max = 0
            : m_ConfigGraphObjectsAlt.scale.max = *maxElement;
        m_Graph3State = GraphState::CanPlot;
    }

}

void dae::TrashCacheComponent::CalculateEx1()
{
    m_XDataIntArray.clear();
    m_YDataIntArray.clear();

    int* pBuffer{ new int[m_BufferSize] {} };

    for (int stepsize{ 1 }; stepsize <= m_MaxSteps; stepsize *= 2)
    {

        m_XDataIntArray.push_back(static_cast<float>(stepsize));

        std::vector<float> samples;
        samples.reserve(m_NumSamplesEx1);

        for (int sample{ 0 }; sample < m_NumSamplesEx1; ++sample)
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
        m_YDataIntArray.push_back(averageElapsedTime / 1000.f);

        samples.clear();
    }

    delete[] pBuffer;
}

void dae::TrashCacheComponent::CalculateEx2()
{
    m_XDataGameObject3D.clear();
    m_YDataGameObject3D.clear();
    m_YDataGameObject3DAlt.clear();
    m_XDataGameObject3DAlt.clear();

    GameObject3D* pBuffer{ new GameObject3D[m_BufferSize]{} };
    GameObject3DAlt* pBufferAlt{ new GameObject3DAlt[m_BufferSize]{} };

    for (int stepsize{ 1 }; stepsize <= m_MaxSteps; stepsize *= 2)
    {

        m_XDataGameObject3D.push_back(static_cast<float>(stepsize));
        m_XDataGameObject3DAlt.push_back(static_cast<float>(stepsize));
        m_XDataGraphcombined.push_back(static_cast<float>(stepsize));


        std::vector<float> samples;
        samples.reserve(m_NumSamplesEx2);

        std::vector<float> samplesAlt;
        samples.reserve(m_NumSamplesEx2);

        for (int sample{ 0 }; sample < m_NumSamplesEx2; ++sample)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < m_BufferSize; i += stepsize)
            {
                pBuffer[i].ID *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            samples.push_back(static_cast<float>(elapsedTime));

            // alternative
            auto startAlt = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m_BufferSize; i += stepsize)
            {

                pBufferAlt[i].ID *= 2;


            }
            auto endAlt = std::chrono::high_resolution_clock::now();
            auto elapsedTimeAlt = std::chrono::duration_cast<std::chrono::microseconds>(endAlt - startAlt).count();
            samplesAlt.push_back(static_cast<float>(elapsedTimeAlt));
        }

        // Remove the highest and lowest value 
        std::sort(samples.begin(), samples.end());
        samples.erase(samples.begin());
        samples.pop_back();

        float averageElapsedTime = std::accumulate(samples.begin(), samples.end(), 0.0f) / samples.size();
        m_YDataGameObject3D.push_back(averageElapsedTime / 1000.f);

        samples.clear();

        // alternative

        std::sort(samplesAlt.begin(), samplesAlt.end());
        samplesAlt.erase(samplesAlt.begin());
        samplesAlt.pop_back();

        float averageElapsedTimeAlt = std::accumulate(samplesAlt.begin(), samplesAlt.end(), 0.0f) / samplesAlt.size();
        m_YDataGameObject3DAlt.push_back(averageElapsedTimeAlt / 1000.f);

        samplesAlt.clear();

    }
    delete[] pBuffer;
    delete[] pBufferAlt;
}

void dae::TrashCacheComponent::CalculateCombined() // PlotCombined
{

    m_YDataGraphcombined.clear();
    m_XDataGraphcombined.clear();

    m_YDataGraphcombined.push_back(m_YDataGameObject3D.data());
    m_YDataGraphcombined.push_back(m_YDataGameObject3DAlt.data());
    m_ConfigCombined.values.ys_list = m_YDataGraphcombined.data();

    m_ConfigCombined.scale.max = m_ConfigCombined.scale.max;
    m_ConfigCombined.values.xs = m_ConfigGraphObjects.values.xs;

    m_ConfigCombined.values.count = static_cast<int>(std::min(m_XDataGameObject3D.size(), m_XDataGameObject3DAlt.size()));
    m_ConfigCombined.scale.max = std::max(m_ConfigGraphObjects.scale.max, m_ConfigGraphObjectsAlt.scale.max);

    ImGui::Plot("combination", m_ConfigCombined);

}