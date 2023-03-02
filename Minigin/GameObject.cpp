
#include "GameObject.h"


void dae::GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		if (component)
		component.get()->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		if(component)
		component.get()->Render();
	}
}