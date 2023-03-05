#pragma once

#include "BaseComponent.h"
//#pragma warning( push )
//#pragma warning( disable: 4201 )
////code with ThatWarning here
//#include "glm/gtc/quaternion.hpp"
//#pragma warning( pop )

#include <glm/glm.hpp>


namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent(std::weak_ptr<GameObject> owner, const std::string& identifier = "");
		~TransformComponent() = default;
		
		void Update() override;
		void UpdateWorldPosition();

		const glm::vec3 GetWorldPosition() const; 
		const glm::vec3 GetLocalPosition() const; 



		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(const glm::vec3& pos);

		void SetPositionDirty();

		const glm::vec3 GetScale() const;
		void setScale(const glm::vec3& scale);
		
	private:
		glm::vec3 m_LocalPosition, m_WorldPosition;
		glm::vec3 m_Scale{ glm::vec3(1.0f) };

		bool m_PositionIsDirty;
	};
}

