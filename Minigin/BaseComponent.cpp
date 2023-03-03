#include "BaseComponent.h"
#include "GameObject.h"


dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> owner)
	: m_pOwner(owner) 
{
}

std::shared_ptr<dae::GameObject> dae::BaseComponent::GetOwner() const
{
	return m_pOwner.lock();
}

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::Render() const
{
}