#pragma once
#include "Component.h"
#include "SDL.h"
#include "glm/glm.hpp"

namespace dae
{
	struct Event;
	class BoxCollider final : public Component
	{
	public:
		BoxCollider(float centerX, float centerY, float w, float h);
		virtual ~BoxCollider();

		virtual void Render() override;

		void Hit(BoxCollider* pOther);

		void SetSize(float w, float h);
		const glm::vec2& GetSize() const;

		void SetCenterPosition(float x, float y);
		const glm::vec2& GetCenterPosition() const;



	private:
		void OnPlayerMove(const Event& event);
		glm::vec2 m_Center;
		glm::vec2 m_Size;
	};

}
