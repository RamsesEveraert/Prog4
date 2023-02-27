#pragma once

#include "BaseComponent.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>


namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent(const std::weak_ptr<GameObject>& gameObject);
		~TransformComponent() = default;
		
		void Update() override;
		void Render() const override;



		const glm::vec3 GetPosition() const; 
		void SetPosition(const glm::vec3& position);

		/*const glm::quat getRotation() const;
		void setRotation(const glm::quat& rotation);*/

		const glm::vec3 GetScale() const;
		void setScale(const glm::vec3& scale);
		
	private:
		glm::vec3 m_Position{ glm::vec3(0.0f) };
		/*glm::quat m_Rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) };*/
		glm::vec3 m_Scale{ glm::vec3(1.0f) };
	};
}

