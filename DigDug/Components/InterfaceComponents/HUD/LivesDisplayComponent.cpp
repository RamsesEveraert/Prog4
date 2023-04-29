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

dae::LivesDisplayComponent::LivesDisplayComponent()
    : m_pHealth{nullptr}, m_Lives{4}, m_pSprite{ nullptr }, m_pOwnerLives{nullptr}
{
    EventQueue::GetInstance().AddListener("PlayerDied", [this](const dae::Event& event) { OnPlayerDied(event); }); // []scope, () parameters, {} fction body
    EventQueue::GetInstance().AddListener("HitEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
    EventQueue::GetInstance().AddListener("HealEvent", [this](const dae::Event& event) { UpdateLivesDisplay(event); });
}

void dae::LivesDisplayComponent::OnPlayerDied(const dae::Event& event)
{
    std::string ownerName{};

    for (const auto& data : event.data)
    {
        if (data.type() == typeid(std::string))
        {
            ownerName = std::any_cast<std::string>(data);
        }
    }

    if (ownerName != m_pOwnerLives->GetObjectName()) return; // Event is not for this player

   /* if (event.name == "PlayerDied")*/
        /*m_pSprite->SetText(m_pOwnerLives->GetObjectName() + " just died, GameOver!");*/
}

void dae::LivesDisplayComponent::UpdateLivesDisplay(const dae::Event& event)
{
    if (event.data.empty())
    {
        std::cerr << "Error: HitEvent data vector is empty" << std::endl;
        return;
    }

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
    auto pChildren{ GetOwner()->GetChildren() };
    int numChildren{ static_cast<int>(pChildren.size() - 1 )};
    if (numChildren > 0)
    {
        // Find the last child with the "Life" name and remove it
        for (int i{ numChildren }; i >= remainingLives; --i)
        {
            auto child = pChildren[i];
            if (child->GetObjectName() == "Life")
            {
                child->MarkForDelete();
                break;
            }
        }
    }

}

void dae::LivesDisplayComponent::SetOwnerLives(GameObject* gameObject)
{
    // Get the Health component and current number of lives
    m_pHealth = gameObject->GetComponent<Health>();
    m_Lives = m_pHealth->GetHealth();

    // set the owner object
    m_pOwnerLives = gameObject;

    // Add multiple Sprite components to the GameObject, one for each life, and a SpriteRenderer component to render it
    for (int i = 0; i <= m_Lives; ++i)
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