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
