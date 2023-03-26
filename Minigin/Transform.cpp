#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform()
	: m_LocalPosition{glm::vec3(0,0,0)}
	, m_WorldPosition{glm::vec3(0,0,0)}
{

}


void dae::Transform::UpdateWorldPosition(const glm::vec3& position)
{
	m_WorldPosition = position;
}

void dae::Transform::SetPosition(float x, float y, float z)
{
	m_LocalPosition = glm::vec3(x, y, z);
}
void dae::Transform::SetPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
}

const glm::vec3 dae::Transform::GetWorldPosition() const
{
	return m_WorldPosition;
}

const glm::vec3 dae::Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::Transform::SetWorldPosition(const glm::vec3& pos)
{
	m_WorldPosition = pos;
}

void dae::Transform::SetPositionDirty()
{
	m_PositionIsDirty = true;
}


const glm::vec3 dae::Transform::GetScale() const
{
	return m_Scale;
}

void dae::Transform::setScale(const glm::vec3& scale)
{
	m_Scale = scale;
}
