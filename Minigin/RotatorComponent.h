#pragma once

#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class RotatorComponent final : public BaseComponent
	{
	public:

		RotatorComponent();
		~RotatorComponent() = default;

		void Update();

		void SetCenterPoint(const glm::vec2& centerPoint);
		const glm::vec2& GetCenterPoint()const;

		void SetRotationSpeed(float degreesPerSecond);
		void SetRadius(float radius);

	private:
		float m_RotationSpeed; // degrees per second
		float m_Radius; // distance from center point
		float m_Angle; // current angle around the center point
		glm::vec2 m_CenterPoint; // position of the center point in world space


	};
}


