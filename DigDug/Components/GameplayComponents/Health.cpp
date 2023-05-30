#include "Health.h"
#include "EventQueue.h"
#include "Event.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Enemies/Enemy.h"

dae::Health::Health()
	: m_Health{ 4 }
	, m_pPlayer{nullptr}
	, m_pEnemy {nullptr}
	, m_pOwner{nullptr}
{
	
}

void dae::Health::Initialize()
{
	EventQueue::GetInstance().AddListener("HitEvent", [this](const dae::Event& event) { OnHit(event); });

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
			else if (collider->GetOwner()->HasComponent<Enemy>()) enemyCollider = collider;;
		}
	}

	if (playerCollider && enemyCollider)
	{
		if (m_pOwner->HasComponent<Player>())
		{
			if (m_Health > 0) --m_Health;

			else if (m_Health <= 0)
			{
				Event dieEvent{ "PlayerDied", { m_Health, m_pOwner->GetObjectName() } };
				EventQueue::GetInstance().Dispatch(dieEvent);
				return;
			}

			{
				Event decreaseLives{ "LiveDecreased", { m_Health, m_pOwner->GetObjectName() } };
				EventQueue::GetInstance().Dispatch(decreaseLives);

				m_pOwner->GetComponent<Player>()->ResetPlayerStartPosition();
			}
		}
	}

}



void dae::Health::Heal()
{
	if (m_Health >= 0)++m_Health;
	{
		Event healEvent{ "HealEvent", { m_Health, GetOwner()->GetObjectName() } };
		EventQueue::GetInstance().Dispatch(healEvent);
	}
	
}

void dae::Health::SetHealth(int health)
{
	m_Health = health;
	if (m_Health <= 0)
	{
		Event dieEvent{ "PlayerDied", { m_Health, GetOwner()->GetObjectName() } };
		EventQueue::GetInstance().Dispatch(dieEvent);
	}; 
}

int dae::Health::GetHealth() const
{
	return m_Health;
}
