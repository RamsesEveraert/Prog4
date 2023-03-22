#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(std::weak_ptr<GameObject> owner, const glm::vec3& startPoint, const std::string& identifier)
	: BaseComponent(owner,identifier), m_LocalPosition{ startPoint }, m_WorldPosition{ glm::vec3(0.0f) }, m_PositionIsDirty{ true }
{

}

void dae::TransformComponent::Update()
{
	if (m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}

	
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

		for (auto& child : GetOwner()->GetChildren())
		{
			child->GetComponent<dae::TransformComponent>()->UpdateWorldPosition();
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
