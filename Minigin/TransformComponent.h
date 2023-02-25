#pragma once

#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent(const std::weak_ptr<GameObject>& gameObject);

		const glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position){ m_Position = position; }

		/*const glm::quat GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; }*/

		const glm::vec3 GetScale() const { return m_Scale; }
		void setScale(const glm::vec3& scale) { m_Scale = scale; }

		
	private:
		glm::vec3 m_Position{ glm::vec3(0.0f) };
		/*glm::quat m_Rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) };*/
		glm::vec3 m_Scale{ glm::vec3(1.0f) };
	};
}
