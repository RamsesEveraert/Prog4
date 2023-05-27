#include "Button.h"
#include "InputManager.h"

dae::Button::Button(const glm::vec2& position, const glm::ivec2& size, std::function<void()> onClickFunction)
	: m_Position {position}
	, m_Size {size}
	, m_OnClickFunction {onClickFunction}
{
	InputManager::GetInstance().AddHUDButton(this);
}

void dae::Button::OnMouseClick(const glm::vec2& mousePos)
{
	std::cout << "Mouseposition [" << std::to_string(mousePos.x) <<", " << std::to_string(mousePos.y) << "]\n";
	std::cout << "ButtonPosition [" << std::to_string(m_Position.x) <<", " << std::to_string(m_Position.y) << "]\n";
	std::cout << "m_Size [" << std::to_string(m_Size.x) <<", " << std::to_string(m_Size.y) << "]\n";
	
	if (mousePos.x > m_Position.x && mousePos.x < m_Position.x + m_Size.x
		&& mousePos.y > m_Position.y && mousePos.y < m_Position.y + m_Size.y)
	{
		m_OnClickFunction();
	}
}
