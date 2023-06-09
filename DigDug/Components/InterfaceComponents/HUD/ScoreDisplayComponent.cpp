#include "ScoreDisplayComponent.h"
#include "EventHandler.h"
#include "ResourceManager.h"
#include "Event.h"
#include "GameObject.h"
#include "Score.h"
#include "Text.h"
#include "Texture.h"

#include <sstream>

dae::ScoreDisplayComponent::ScoreDisplayComponent()
    : m_pScore{ nullptr }, m_Score{ 0 }, m_HighScore{ 0 }, m_pOwnerScore {
    nullptr
}, m_pTextcomponent{ nullptr }
{
    EventHandler::GetInstance().AddListener("PlayerDied", [this](const dae::Event& event) { OnPlayerDied(event); }); // []scope, () parameters, {} fction body
    EventHandler::GetInstance().AddListener("DecrementEvent", [this](const dae::Event& event) { UpdateScoreDisplay(event); });
    EventHandler::GetInstance().AddListener("IncrementScore", [this](const dae::Event& event) { UpdateScoreDisplay(event); });
}

void dae::ScoreDisplayComponent::UpdateScoreDisplay(const dae::Event& event)
{
    if (event.data.empty())
    {
        std::cerr << "Error: data vector is empty" << std::endl;
        return;
    }

    int updatedScore = 0;
    std::string ownerName;
    for (const auto& data : event.data)
    {
        if (data.type() == typeid(int))
        {
            updatedScore = std::any_cast<int>(data);
        }
        else if (data.type() == typeid(std::string))
        {
            ownerName = std::any_cast<std::string>(data);
        }
    }

    if (ownerName != m_pOwnerScore->GetObjectName()) return; // Event is not for this player
    
    std::stringstream ss;
    ss << "Score " << m_pOwnerScore->GetObjectName() << ":" << updatedScore;
    m_pTextcomponent->SetText(ss.str());
}

void dae::ScoreDisplayComponent::OnPlayerDied(const dae::Event& event)
{
    std::string ownerName;

    for (const auto& data : event.data)
    {
        if (data.type() == typeid(std::string))
        {
            ownerName = std::any_cast<std::string>(data);
        }
    }

    if (ownerName != m_pOwnerScore->GetObjectName()) return; // Event is not for this player
    if (event.name == "PlayerDied")
        m_pTextcomponent->SetText("Score " + m_pOwnerScore->GetObjectName() + ":    0, Player died :(");
}

void dae::ScoreDisplayComponent::ShowScore(GameObject* gameObject)
{
    m_pScore = gameObject->GetComponent<Score>();
    m_Score = m_pScore->GetScore();
    m_pTextcomponent = gameObject->GetComponent<Text>();
    m_pOwnerScore = gameObject;

    if (!m_pTextcomponent)
    {
        if (!GetOwner()->HasComponent<Texture>()) GetOwner()->AddComponent<Texture>("");
        m_pTextcomponent = GetOwner()->AddComponent<Text>();
        m_pTextcomponent->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
    }

    m_pTextcomponent->SetText("Score " + m_pOwnerScore->GetObjectName() + ":    " + std::to_string(m_Score));
}

void dae::ScoreDisplayComponent::ShowHighScore(GameObject* gameObject)
{
    m_pScore = gameObject->GetComponent<Score>();
    m_HighScore = m_pScore->GetHighScore();
    m_pTextcomponent = gameObject->GetComponent<Text>();
    m_pOwnerScore = gameObject;

    if (!m_pTextcomponent)
    {
        if (!GetOwner()->HasComponent<Texture>()) GetOwner()->AddComponent<Texture>("");
        m_pTextcomponent = GetOwner()->AddComponent<Text>();
        m_pTextcomponent->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
    }

    m_pTextcomponent->SetText(m_pOwnerScore->GetObjectName() + ": " + std::to_string(m_HighScore));
}
