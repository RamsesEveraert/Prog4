#include "Health.h"
#include "EventQueue.h"
#include "Event.h"
#include "GameObject.h"
#include "BoxCollider.h"

dae::Health::Health()
	: m_Health{ 3 }
{
	EventQueue::GetInstance().AddListener("HitEvent", [this](const dae::Event& event) { OnHit(event); });
}

void dae::Health::OnHit(const dae::Event& event)
{
	std::string ownerName{};
	for (const auto& data : event.data)
	{
		if (data.type() == typeid(BoxCollider*))
		{
			//BoxCollider* collisionObject = std::any_cast<BoxCollider*>(data); 
			//if (collisionObject->GetOwner()->GetObjectName() != GetOwner()->GetObjectName()) return; // owner of collision object is not the owner of this health component
			//else 
		}
			
		if (data.type() == typeid(std::string))
		{
			ownerName = std::any_cast<std::string>(data);
		}
	}

	//if (ownerName != m_pOwnerLives->GetObjectName()) return; // Event is not for this player
	if (m_Health > 0) --m_Health;
	if (m_Health <= 0)
	{
		Event dieEvent{ "PlayerDied", { m_Health, GetOwner()->GetObjectName() } };
		EventQueue::GetInstance().Dispatch(dieEvent);
		return;
	}

	{
		Event hitEvent{ "HitEvent", { m_Health, GetOwner()->GetObjectName() } };
		EventQueue::GetInstance().Dispatch(hitEvent);
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
