#include "Health.h"
#include "EventQueue.h"
#include "Event.h"

dae::Health::Health()
	: m_Health{ 3 }
{

}

void dae::Health::Hit()
{
	if (m_Health > 0) --m_Health;
	if (m_Health <= 0)
	{
		EventQueue::GetInstance().Dispatch(Event{ "PlayerDied" });
		return;
	}

	
	Event hitEvent{ "HitEvent", { m_Health } };
	EventQueue::GetInstance().Dispatch(hitEvent);
}

void dae::Health::Heal()
{
	if (m_Health >= 0)++m_Health;
	Event healEvent{ "HealEvent", { m_Health } };
	EventQueue::GetInstance().Dispatch(healEvent);
}

void dae::Health::SetHealth(int health)
{
	m_Health = health;
	if (m_Health <= 0)
	{
		EventQueue::GetInstance().Dispatch(Event{ "PlayerDied" });
	}; 
}

int dae::Health::GetHealth() const
{
	return m_Health;
}
