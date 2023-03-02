#include "BaseComponent.h"
#include "GameObject.h"

std::weak_ptr<dae::GameObject> dae::BaseComponent::GetOwner() const
{
	return m_pOwner;
}

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::Render() const
{
}

