#pragma once

#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent(const std::weak_ptr<GameObject>& gameObject);
		~TransformComponent() = default;
		
		void Update(/*float deltaTime*/) override;
		void Render() const override;



		const glm::vec3 getPosition() const { return m_position; }
		void setPosition(const glm::vec3& position){ m_position = position; }

		/*const glm::quat getRotation() const { return m_Rotation; }
		void setRotation(const glm::quat& rotation) { m_Rotation = rotation; }*/

		const glm::vec3 getScale() const { return m_scale; }
		void setScale(const glm::vec3& scale) { m_scale = scale; }
		
	private:
		glm::vec3 m_position{ glm::vec3(0.0f) };
		/*glm::quat m_rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) };*/
		glm::vec3 m_scale{ glm::vec3(1.0f) };
	};
}

