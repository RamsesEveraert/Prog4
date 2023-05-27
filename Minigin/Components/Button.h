#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include <functional>

namespace dae
{
	// hulp gekregen van Jarne Wieme

	class Button final : public Component
	{
	public:
		Button(const glm::vec2& position, const glm::ivec2& size, std::function<void()> onClickFunction);
		void OnMouseClick(const glm::vec2& mousePos);

	private:
		glm::vec2 m_Position;
		const glm::ivec2& m_Size;
		std::function<void()> m_OnClickFunction;
	};

}

