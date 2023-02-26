
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "Renderer.h"

#include <string>



dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	/*for (const auto& componentPtr : m_ComponentPointers)
	{
		if(componentPtr)
		componentPtr.get()->Update();
	}*/
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		if(component)
		component.get()->Render();
	}
}