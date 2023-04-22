#include "Component.h"
#include "GameObject.h"


using namespace dae;


Component::Component()
	: m_pOwner{}
{

}

GameObject* Component::GetOwner() const
{
	return m_pOwner;
}

void Component::SetOwner(GameObject* owner)
{
	m_pOwner = owner;
}


void Component::Update()
{
}

void Component::FixedUpdate()
{
}

void Component::Render()
{
}

void Component::RenderImGui()
{
}
