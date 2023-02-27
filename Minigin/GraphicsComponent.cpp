#include "GraphicsComponent.h"

dae::GraphicsComponent::GraphicsComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject)
{
}
