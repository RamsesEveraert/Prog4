#include "LivesDisplayComponent.h"
#include "EventQueue.h"
#include "ResourceManager.h"
#include "Event.h"
#include "GameObject.h"
#include "Health.h"
#include "TextComponent.h"
#include "TextureComponent.h"

#include <sstream>

using namespace dae;

dae::LivesDisplayComponent::LivesDisplayComponent()
    : m_pHealth{nullptr}, m_Lives{3}, m_pTextcomponent{ nullptr }, m_pOwnerLives{nullptr}
{
    EventQueue::GetInstance().AddListener("PlayerDied", [this](const dae::Event& event) { OnPlayerDied(event); }); // []scope, () parameters, {} fction body
    EventQueue::GetInstance().AddListener("HitEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
    EventQueue::GetInstance().AddListener("HealEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
}

dae::LivesDisplayComponent::~LivesDisplayComponent()
{
    EventQueue::GetInstance().RemoveListener("PlayerDied", [this](const dae::Event& event) { OnPlayerDied(event); }); 
    EventQueue::GetInstance().RemoveListener("HitEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
    EventQueue::GetInstance().RemoveListener("HealEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
}

void dae::LivesDisplayComponent::OnPlayerDied(const dae::Event& event)
{
    std::string ownerName;

    for (const auto& data : event.data)
    {
        if (data.type() == typeid(std::string))
        {
            ownerName = std::any_cast<std::string>(data);
        }
    }

    if (ownerName != m_pOwnerLives->GetObjectName()) return; // Event is not for this player

    if (event.name == "PlayerDied")
        m_pTextcomponent->SetText(m_pOwnerLives->GetObjectName() + " just died, GameOver!");
}

void dae::LivesDisplayComponent::UpdateLivesDisplay(const dae::Event& event)
{
    if (event.data.empty())
    {
        std::cerr << "Error: HitEvent data vector is empty" << std::endl;
        return;
    }

    int remainingLives = 0;
    std::string ownerName;
    for (const auto& data : event.data)
    {
        if (data.type() == typeid(int))
        {
            remainingLives = std::any_cast<int>(data);
        }
        else if (data.type() == typeid(std::string))
        {
            ownerName = std::any_cast<std::string>(data);
        }
    }

    if (ownerName != m_pOwnerLives->GetObjectName()) return; // Event is not for this player

    std::stringstream ss;
    ss << "Lives " << m_pOwnerLives->GetObjectName() << ":    " << remainingLives;
    m_pTextcomponent->SetText(ss.str());
}

void dae::LivesDisplayComponent::SetOwnerLives(GameObject* gameObject)
{
    m_pHealth = gameObject->GetComponent<Health>();
    m_Lives = m_pHealth->GetHealth();
    m_pTextcomponent = gameObject->GetComponent<TextComponent>();
    m_pOwnerLives = gameObject;

    if (!m_pTextcomponent)
    {
        if (!GetOwner()->HasComponent<TextureComponent>()) GetOwner()->AddComponent<TextureComponent>();
        m_pTextcomponent = GetOwner()->AddComponent<TextComponent>();
        m_pTextcomponent->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
    }

    m_pTextcomponent->SetText("Lives " + m_pOwnerLives->GetObjectName() + ":    " + std::to_string(m_Lives));
}