#pragma once

#include "RotatorComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace dae
{
	RotatorComponent::RotatorComponent()
		: m_CenterPoint(glm::vec3(0,0,0)), 
		m_RotationSpeed(0.0f), 
		m_Radius{0}, 
		m_Angle(0.0f)
	{
		
	}

	void RotatorComponent::Update()
	{
			auto& timer = Timer::GetInstance();

			// Calculate new angle based on time passed and rotation speed
			const float dt = timer.getDeltaTimeSec();

			m_Angle += m_RotationSpeed * dt;

			if (m_Angle >= 360.f) m_Angle -= 360.f;

			// Calculate new position using center point and angle

			glm::vec3 newPos = m_CenterPoint + (glm::vec3(cos(m_Angle), sin(m_Angle), 0.0f)) * m_Radius;
			GetOwner()->GetTransform()->SetPosition(newPos);
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
