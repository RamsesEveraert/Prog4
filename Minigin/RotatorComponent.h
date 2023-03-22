#pragma once

#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class RotatorComponent final : public BaseComponent
	{
	public:

		RotatorComponent(std::weak_ptr<GameObject> pOwner, const glm::vec3& cnterPoint = glm::vec3(0,0,0), const std::string& identifier = "");
		~RotatorComponent() = default;

		void Update();

		void SetCenterPoint(const glm::vec3& centerPoint);
		const glm::vec3& GetCenterPoint()const;

		void SetRotationSpeed(float degreesPerSecond);
		void SetRadius(float radius);

	private:
		std::shared_ptr<TransformComponent> m_TransformComponent;
		float m_RotationSpeed; // degrees per second
		float m_Radius; // distance from center point
		float m_Angle; // current angle around the center point
		glm::vec3 m_CenterPoint; // position of the center point in world space


	};
}


