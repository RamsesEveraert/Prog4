#include "Transform.h"
#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace dae;

Transform::Transform()
	: m_LocalPosition{}
	, m_WorldPosition{}
	, m_Scale{1.0f}
	, m_Rotation{}
	, m_IsTransformDirty{true}
{

}


void Transform::UpdateWorldPosition()
{
	m_IsTransformDirty = false;
	auto pParent = GetOwner()->GetParent();

	if (pParent != nullptr)
	{
		m_WorldPosition = m_LocalPosition + pParent->GetTransform()->GetWorldPosition();
	}
	else
	{
		m_WorldPosition = m_LocalPosition;
	}
}

void Transform::SetDirty()
{
	m_IsTransformDirty = true;

	auto pOwner = GetOwner();
	if (!pOwner) return;

	const auto& pChildren= pOwner->GetChildren();
	for (const auto& child : pChildren)
	{
		const auto pTransform{ child->GetTransform() };
		if (!pTransform) continue;

		pTransform->SetDirty();
	}

}
bool Transform::IsDirty()
{
	return m_IsTransformDirty;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_LocalPosition = glm::vec3(x, y, z);
	SetDirty();
}
void Transform::SetPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetDirty();
}
void Transform::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition = glm::vec3(x, y, z);
	SetDirty();
}
void Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetDirty();
}
void Transform::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition = glm::vec3(x,y,z);
	SetDirty();
}
void Transform::SetWorldPosition(const glm::vec3& pos)
{
	m_WorldPosition = pos;
	SetDirty();
}

const glm::vec3 Transform::GetWorldPosition() const
{
	return m_WorldPosition;
}
const glm::vec3 Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3 Transform::GetScale() const
{
	return m_Scale;
}
void Transform::setScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

glm::vec3 Transform::Translate(float x, float y, float z)
{
	SetDirty();
	glm::vec3 translation(x, y, z);
	m_LocalPosition += translation;

	return m_LocalPosition;
}
glm::vec3 Transform::Translate(const glm::vec3& translation)
{
	SetDirty();

	m_LocalPosition += translation;

	return m_LocalPosition;
}
