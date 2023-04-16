#include "ScoreDisplayComponent.h"
#include "EventQueue.h"
#include "ResourceManager.h"
#include "Event.h"
#include "GameObject.h"
#include "Score.h"
#include "TextComponent.h"
#include "TextureComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent()
    : m_pScore{nullptr}, m_Score{0}, m_pOwnerScore {nullptr}, m_pTextcomponent{ nullptr }
{
    EventQueue::GetInstance().AddListener("PlayerDied", std::bind(&ScoreDisplayComponent::OnPlayerDied, this, std::placeholders::_1));
    EventQueue::GetInstance().AddListener("DecrementEvent", std::bind(&ScoreDisplayComponent::UpdateScoreDisplay, this, std::placeholders::_1));
    EventQueue::GetInstance().AddListener("IncrementScore", std::bind(&ScoreDisplayComponent::UpdateScoreDisplay, this, std::placeholders::_1));
}

void dae::ScoreDisplayComponent::UpdateScoreDisplay(const dae::Event& event)
{
    if (event.data.empty())
    {
        std::cerr << "Error: data vector is empty" << std::endl;
        return;
    }

    int updatedScore = std::any_cast<int>(event.data[0]);
    m_pTextcomponent->SetText("Score " + m_pOwnerScore->GetObjectName() + ":    " + std::to_string(updatedScore));
}

void dae::ScoreDisplayComponent::OnPlayerDied(const dae::Event& event)
{
    if (event.name == "PlayerDied")
        m_pTextcomponent->SetText("Score " + m_pOwnerScore->GetObjectName() + ":    0, Player died :(");
}

void dae::ScoreDisplayComponent::SetOwnerScore(GameObject* gameObject)
{
    m_pScore = gameObject->GetComponent<Score>();
    m_Score = m_pScore->GetScore();
    m_pTextcomponent = gameObject->GetComponent<TextComponent>();
    m_pOwnerScore = gameObject;

    if (!m_pTextcomponent)
    {
        if (!GetOwner()->HasComponent<TextureComponent>()) GetOwner()->AddComponent<TextureComponent>();
        m_pTextcomponent = GetOwner()->AddComponent<TextComponent>();
        m_pTextcomponent->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
    }

    m_pTextcomponent->SetText("Score " + m_pOwnerScore->GetObjectName() + ":    " + std::to_string(m_Score));
}
