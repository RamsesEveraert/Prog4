#include "BaseComponent.h"
#include "GameObject.h"

std::shared_ptr<dae::GameObject> dae::BaseComponent::GetParent() const
{
	return m_Parent.lock();
}

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::Render() const
{
}
