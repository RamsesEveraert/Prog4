#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject), m_LocalPosition{ glm::vec3(0.0f) }, m_WorldPosition{ glm::vec3(0.0f) }, m_PositionIsDirty{ true }
{

}

void dae::TransformComponent::Update()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
}

void dae::TransformComponent::UpdateWorldPosition()
{
		
		if (GetOwner()->GetParent() == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			auto worldPositionParent = GetOwner()->GetParent()->GetComponent<dae::TransformComponent>()->GetWorldPosition();
			m_WorldPosition = worldPositionParent + m_LocalPosition;
		}	
			
		m_PositionIsDirty = false;
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

void dae::TransformComponent::SetPositionDirty()
{
	m_PositionIsDirty = true;
}

//const glm::quat dae::TransformComponent::getRotation() const
//{
//	return m_Rotation;
//}
//
//void dae::TransformComponent::setRotation(const glm::quat& rotation)
//{
//	m_Rotation = rotation;
//}

const glm::vec3 dae::TransformComponent::GetScale() const
{
	return m_Scale;
}

void dae::TransformComponent::setScale(const glm::vec3& scale)
{
	m_Scale = scale;
}
