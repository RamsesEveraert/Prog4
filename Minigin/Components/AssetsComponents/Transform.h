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
		const glm::vec2 GetWorldPosition() const; 
		const glm::vec2 GetLocalPosition() const; 

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& pos);
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(const glm::vec2& pos);

		// scaling
		const glm::vec2 GetScale() const;
		void setScale(const glm::vec2& scale);

		// translate

		glm::vec2 Translate(float x, float y);
		glm::vec2 Translate(const glm::vec2& translation);

	private:
		glm::vec2 m_LocalPosition, m_WorldPosition;
		glm::vec2 m_Scale;;
		glm::quat m_Rotation;

		bool m_IsTransformDirty;
	};
}

