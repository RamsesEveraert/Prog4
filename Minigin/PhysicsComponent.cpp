#include "PhysicsComponent.h"

dae::PhysicsComponent::PhysicsComponent(std::weak_ptr<GameObject> owner, const std::string& identifier)
	:BaseComponent(owner, identifier)
{
}