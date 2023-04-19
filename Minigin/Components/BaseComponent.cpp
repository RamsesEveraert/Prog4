#include "BaseComponent.h"
#include "GameObject.h"


using namespace dae;

GameObject* BaseComponent::GetOwner() const
{
	return m_pOwner;
}

void BaseComponent::SetOwner(GameObject* owner)
{
	m_pOwner = owner;
}

const std::string BaseComponent::GetIdentifier() const
{
	return m_Identifier;
}


void BaseComponent::Update()
{
}

void BaseComponent::FixedUpdate()
{
}

void BaseComponent::Render()
{
}

void BaseComponent::RenderImGui()
{
}
