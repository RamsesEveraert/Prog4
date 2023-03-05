#include "GraphicsComponent.h"

dae::GraphicsComponent::GraphicsComponent(std::weak_ptr<GameObject> owner, const std::string& identifier)
	: BaseComponent(owner, identifier)
{
}