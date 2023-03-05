#include "InputComponent.h"

dae::InputComponent::InputComponent(std::weak_ptr<GameObject> owner, const std::string& identifier)
	: BaseComponent(owner, identifier)
{
}