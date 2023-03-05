#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> owner, const std::string& identifier)
	:m_pOwner{ owner }, m_Identifier{ identifier }
{
}
std::shared_ptr<dae::GameObject> dae::BaseComponent::GetOwner() const
{
	return m_pOwner.lock();
}

const std::string dae::BaseComponent::GetIdentifier() const
{
	return m_Identifier;
}

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::FixedUpdate()
{
}

void dae::BaseComponent::Render() const
{
}
