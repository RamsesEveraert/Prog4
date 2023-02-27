
#include "GameObject.h"


void dae::GameObject::Update(/*deltaTime*/)
{
	for (const auto& component : m_Components)
	{
		if (component)
		component.get()->Update(/*deltaTime*/);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{

		// every component renders (for possible debug use of certain components)

		if(component)
		component.get()->Render();
	}
}