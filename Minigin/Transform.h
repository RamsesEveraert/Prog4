#pragma once

//#pragma warning( push )
//#pragma warning( disable: 4201 )
////code with ThatWarning here
//#include "glm/gtc/quaternion.hpp"
//#pragma warning( pop )

#include <glm/glm.hpp>


namespace dae
{
	class Transform final
	{
	public:

		Transform();
		~Transform() = default;
		
		void UpdateWorldPosition(const glm::vec3& position);

		const glm::vec3 GetWorldPosition() const; 
		const glm::vec3 GetLocalPosition() const; 


		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& pos);

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

