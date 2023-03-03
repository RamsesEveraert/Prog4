#pragma once

#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include <cmath>

namespace dae
{
	RotatorComponent::RotatorComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject), m_CenterPoint(glm::vec3(0.0f)), m_RotationSpeed(0.0f), m_Angle(0.0f)
	{
		if (gameObject.lock()->hasComponent<dae::TransformComponent>())
		{
			m_TransformComponent = gameObject.lock()->GetComponent<dae::TransformComponent>();
		}
	}

	void RotatorComponent::Update()
	{
		if (m_TransformComponent)
		{
			// Calculate new angle based on time passed and rotation speed
			const float deltaTime = Timer::GetInstance().getDeltaTimeMs();
			m_Angle += m_RotationSpeed * deltaTime;

			// Calculate new position using center point and angle
			glm::vec3 newPos = m_CenterPoint + glm::vec3(cos(m_Angle), sin(m_Angle), 0.0f);
			m_TransformComponent->SetLocalPosition(newPos);
		}
	}

	void RotatorComponent::SetCenterPoint(const glm::vec3& centerPoint)
	{
		m_CenterPoint = centerPoint;
	}

	void RotatorComponent::SetRotationSpeed(float speed)
	{
		m_RotationSpeed = speed;
	}
}
