#include "LivesDisplayComponent.h"
#include "EventQueue.h"
#include "ResourceManager.h"
#include "Event.h"
#include "GameObject.h"
#include "Health.h"
#include "TextComponent.h"
#include "TextureComponent.h"

using namespace dae;

dae::LivesDisplayComponent::LivesDisplayComponent()
    : m_pHealth{}, m_Lives{}, m_pTextcomponent{ }, m_pOwnerLives{}
{
    EventQueue::GetInstance().AddListener("PlayerDied", std::bind(&LivesDisplayComponent::OnPlayerDied, this, std::placeholders::_1));
    EventQueue::GetInstance().AddListener("HitEvent", std::bind(&LivesDisplayComponent::UpdateLivesDisplay, this, std::placeholders::_1));
    EventQueue::GetInstance().AddListener("HealEvent", std::bind(&LivesDisplayComponent::UpdateLivesDisplay, this, std::placeholders::_1));
}

void dae::LivesDisplayComponent::OnPlayerDied(const dae::Event& event)
{
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

    int remainingLives = std::any_cast<int>(event.data[0]);
    m_pTextcomponent->SetText("Lives " + m_pOwnerLives->GetObjectName() + ":    " + std::to_string(remainingLives));
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
