
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Renderer.h"

#include <string>



dae::GameObject::~GameObject() = default;

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
		if(component)
		component.get()->Render();
	}
}