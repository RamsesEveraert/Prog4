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
	class Transform final : public BaseComponent
	{
	public:

		Transform();
		~Transform() = default;
		
		void UpdateWorldPosition();
		void SetDirty();
		bool IsDirty();

		// position
		const glm::vec3 GetWorldPosition() const; 
		const glm::vec3 GetLocalPosition() const; 

		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(float x, float y, float z = 0);
		void SetWorldPosition(const glm::vec3& pos);

		// scaling
		const glm::vec3 GetScale() const;
		void setScale(const glm::vec3& scale);

		// translate

		glm::vec3 Translate(float x, float y, float z = 0);
		glm::vec3 Translate(const glm::vec3& translation);

	private:
		glm::vec3 m_LocalPosition, m_WorldPosition;
		glm::vec3 m_Scale;;
		glm::quat m_Rotation;

		bool m_IsTransformDirty;
	};
}

