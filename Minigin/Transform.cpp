#include "Transform.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent()
	: m_LocalPosition{glm::vec3(0,0,0)}
	, m_WorldPosition{glm::vec3(0,0,0)}
{

}


void dae::TransformComponent::UpdateWorldPosition(const glm::vec3& position)
{
	m_WorldPosition = position;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_LocalPosition = glm::vec3(x, y, z);
}
void dae::TransformComponent::SetPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
}

const glm::vec3 dae::TransformComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}

const glm::vec3 dae::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::TransformComponent::SetWorldPosition(const glm::vec3& pos)
{
	m_WorldPosition = pos;
}

void dae::TransformComponent::SetPositionDirty()
{
	m_PositionIsDirty = true;
}


const glm::vec3 dae::TransformComponent::GetScale() const
{
	return m_Scale;
}

void dae::TransformComponent::setScale(const glm::vec3& scale)
{
	m_Scale = scale;
}
