#include "InputComponent.h"

dae::InputComponent::InputComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject)
{
}
