#pragma once

#include "BaseComponent.h"
#pragma warning( push )
#pragma warning( disable: 4201 )
//code with ThatWarning here
#include "glm/gtc/quaternion.hpp"
#pragma warning( pop )

#include <glm/glm.hpp>


namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent(const std::weak_ptr<GameObject>& gameObject);
		~TransformComponent() = default;
		
		void Update() override;
		void UpdateWorldPosition();

		const glm::vec3 GetWorldPosition() const; 
		const glm::vec3 GetLocalPosition() const; 



		void SetLocalPosition(const glm::vec3& pos);

		void SetPositionDirty();

		/*const glm::quat getRotation() const;
		void setRotation(const glm::quat& rotation);*/

		const glm::vec3 GetScale() const;
		void setScale(const glm::vec3& scale);
		
	private:
		glm::vec3 m_LocalPosition, m_WorldPosition;

		/*glm::quat m_Rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) };*/
		glm::vec3 m_Scale{ glm::vec3(1.0f) };

		bool m_PositionIsDirty;
	};
}

