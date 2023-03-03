#pragma once

#include "BaseComponent.h"

namespace dae
{
	class TransformComponent;
	class RotatorComponent final : public BaseComponent
	{
	public:

		RotatorComponent(const std::weak_ptr<GameObject>& gameObject);
		~RotatorComponent() = default;

		void Update();

		void SetCenterPoint(const glm::vec3& centerPoint);
		void SetRotationSpeed(float speed);

	private:
		glm::vec3 m_CenterPoint;
		float m_RotationSpeed;
		float m_Angle;

		std::shared_ptr<dae::TransformComponent> m_TransformComponent;

	};
}
