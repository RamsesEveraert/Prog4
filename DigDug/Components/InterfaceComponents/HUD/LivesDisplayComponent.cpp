#include "LivesDisplayComponent.h"
#include "EventQueue.h"
#include "ResourceManager.h"
#include "Event.h"
#include "GameObject.h"
#include "Health.h"
#include "Text.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"

#include <sstream>

using namespace dae;

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* player)
    : m_pHealth{nullptr}, m_Lives{}, m_pSprite{ nullptr }, m_pOwnerLives{ player }
{
    EventQueue::GetInstance().AddListener("PlayerDied", [this](const dae::Event& event) { OnPlayerDied(event); }); // []scope, () parameters, {} fction body
    EventQueue::GetInstance().AddListener("LiveDecreased", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
    EventQueue::GetInstance().AddListener("HealEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });

}

void dae::LivesDisplayComponent::UpdateLivesDisplay(const dae::Event& event)
{
    std::cout << "livesdisplaycomponent update called\n";
    int remainingLives{};
    std::string ownerName{};
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

    // Remove a life sprite from the display
    auto pChildren = GetOwner()->GetChildren();
    int numChildren = static_cast<int>(pChildren.size());

    if (numChildren > 0)
    {
        // Find the last child with the "Life" name and remove it
        for (int i = numChildren - 1; i >= remainingLives; --i)
        {
            auto name = "Life" + std::to_string(i);
            auto child = pChildren[i];

            if (child->GetObjectName() == name)
            {
                child->MarkForDelete();
                child->SetParent(nullptr, true);
                break;
            }
        }
    }


}

void dae::LivesDisplayComponent::InitializeLivesSprites()
{
    // Get the Health component and current number of lives
    m_pHealth = m_pOwnerLives->GetComponent<Health>();
    m_Lives = m_pHealth->GetHealth();

    // Add multiple Sprite components to the GameObject, one for each life, and a SpriteRenderer component to render it
    for (int i{}; i < m_Lives; ++i)
    {
        auto name{ "Life" + std::to_string(i) };
        auto lifeSprite{ std::make_shared<GameObject>(name) };
        lifeSprite->AddComponent<Sprite>("General_Sprites.png", SDL_Rect(109, 58, 16, 16), 1.5f);
        lifeSprite->AddComponent<SpriteRenderer>();
        lifeSprite->SetParent(GetOwner(), false);

        // Set the position of the sprite relative to the parent object
        lifeSprite->GetTransform()->SetPosition(i * 32.f, 0);
    }
}