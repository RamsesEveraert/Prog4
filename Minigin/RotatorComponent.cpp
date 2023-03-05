#pragma once

#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace dae
{
	RotatorComponent::RotatorComponent(const std::weak_ptr<GameObject>& gameObject)
		: BaseComponent(gameObject), m_IsTransformComponentChecked{false}, m_CenterPoint(glm::vec3(0.0f)), m_RotationSpeed(0.0f), m_Radius{0}, m_Angle(0.0f)
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
			auto& timer = Timer::GetInstance();
			// Calculate new angle based on time passed and rotation speed
			const float dt = timer.getDeltaTimeMs();
			const float dtSecs = timer.msToSeconds(dt);

			m_Angle += m_RotationSpeed * dtSecs;

			// Calculate new position using center point and angle

			glm::vec3 newPos = m_CenterPoint + (glm::vec3(cos(m_Angle), sin(m_Angle), 0.0f)) * m_Radius;

			m_TransformComponent->SetLocalPosition(newPos);
		}
	}




	void RotatorComponent::SetCenterPoint(const glm::vec3& centerPoint)
	{
		m_CenterPoint = centerPoint;
	}

	const glm::vec3& RotatorComponent::GetCenterPoint()const
	{
		return m_CenterPoint;
	}

	void RotatorComponent::SetRotationSpeed(float degreesPerSecond)
	{
		m_RotationSpeed = degreesPerSecond;
	}
	void RotatorComponent::SetRadius(float radius)
	{
		m_Radius = radius;
	}
}