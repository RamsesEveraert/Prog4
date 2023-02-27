#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject)
{

}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render() const
{
}

const glm::vec3 dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::SetPosition(const glm::vec3& position)
{
	m_Position = position;
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
