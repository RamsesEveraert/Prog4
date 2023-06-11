#include "Health.h"
#include "EventHandler.h"
#include "Event.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Player.h"
#include "../Pooka.h"

dae::Health::Health()
	: m_Health{ 4 }
	, m_pPlayer{nullptr}
	, m_pEnemy {nullptr}
	, m_pOwner{nullptr}
{
	
}

void dae::Health::Initialize()
{
	EventHandler::GetInstance().AddListener("HitEvent", [this](const dae::Event& event) { OnHit(event); });

	m_pOwner = GetOwner();
	if (m_pOwner->HasComponent<Player>()) m_pPlayer = m_pOwner->GetComponent<Player>();
	if (m_pOwner->HasComponent<Enemy>()) m_pEnemy = m_pOwner->GetComponent<Enemy>();
}

void dae::Health::OnHit(const dae::Event& event)
{
	
	BoxCollider* playerCollider{};
	BoxCollider* enemyCollider{};
	/*BoxCollider* pumpCollider{};
	BoxCollider* rockCollider{};*/

	for (const auto& data : event.data)
	{
		if (data.type() == typeid(BoxCollider*))
		{
			BoxCollider* collider = std::any_cast<BoxCollider*>(data);
			if (collider->GetOwner()->HasComponent<Player>()) playerCollider = collider;
			else if (collider->GetOwner()->HasComponent<Pooka>()) enemyCollider = collider;;
		}
	}

	if (playerCollider->GetOwner() != GetOwner()) return; // Event is not for this player

	if (playerCollider && enemyCollider)
	{
		if (m_pOwner->HasComponent<Player>())
		{
			if (m_Health > 0)
			{
				--m_Health;

				Event decreaseLives{ "LiveDecreased", { m_Health, m_pOwner->GetObjectName() } };
				EventHandler::GetInstance().Dispatch(decreaseLives);

				m_pOwner->GetComponent<Player>()->ResetPlayerStartPosition();
			}


			if (m_Health <= 0) 
			{
			/*	Event playerDiedEvent{ "PlayerDied", {m_pOwner->GetObjectName()} };
				EventHandler::GetInstance().Dispatch(playerDiedEvent);*/
			}
		}
	}

}


void dae::Health::SetHealth(int health)
{
	m_Health = health;
	if (m_Health <= 0)
	{
		Event playerDiedEvent{ "PlayerDied", { } };
		EventHandler::GetInstance().Dispatch(playerDiedEvent);
	}; 
}

int dae::Health::GetHealth() const
{
	return m_Health;
}
