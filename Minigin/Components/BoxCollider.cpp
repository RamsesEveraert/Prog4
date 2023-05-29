#include "BoxCollider.h"
#include "CollisionHandler.h"

#include "GameObject.h"
#include "Transform.h"

#include "Renderer.h"
#include "EventQueue.h"

#include "Event.h"

dae::BoxCollider::BoxCollider(float centerX, float centerY, float w, float h)
	: m_Center{ centerX, centerY }
	, m_Size{ w, h }
{
	dae::CollisionHandler::GetInstance().AddCollider(this);
	EventQueue::GetInstance().AddListener("PlayerMoved", [this](const dae::Event& event) { OnPlayerMove(event); }); 
}

dae::BoxCollider::~BoxCollider()
{
	dae::CollisionHandler::GetInstance().RemoveCollider(this);
}

void dae::BoxCollider::Render()
{

	SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();
	// boxcollision
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // purple color
	SDL_Rect collisionBox{ static_cast<int>(m_Center.x - m_Size.x * 0.5f), static_cast<int>(m_Center.y - m_Size.y * 0.5f), static_cast<int>(m_Size.x), static_cast<int>(m_Size.y) };
	SDL_RenderDrawRect(renderer, &collisionBox);
}

void dae::BoxCollider::Hit(BoxCollider* pOther)
{
	std::cout << "hitevent dispatched \n";
	Event hitEvent{ "HitEvent", {this, pOther} };
	EventQueue::GetInstance().Dispatch(hitEvent);
}


void dae::BoxCollider::SetSize(float w, float h)
{
	m_Size = glm::vec2{ w,h };
}

const glm::vec2& dae::BoxCollider::GetSize() const
{
	return m_Size;
}

void dae::BoxCollider::SetCenterPosition(float x, float y)
{
	m_Center = glm::vec2{ x,y };
}

const glm::vec2& dae::BoxCollider::GetCenterPosition() const
{
	return m_Center;
}

void dae::BoxCollider::OnPlayerMove(const Event& event)
{
	std::string ownerName{};
	glm::vec2 playerCenter{};

	for (const auto& data : event.data)
	{
		if (data.type() == typeid(std::string))
		{
			ownerName = std::any_cast<std::string>(data);
		}
		if (data.type() == typeid(glm::vec2))
		{
			playerCenter = std::any_cast<glm::vec2>(data);
		}
	}

	if (ownerName != GetOwner()->GetObjectName()) return; // Event is not for this player

	SetCenterPosition(playerCenter.x, playerCenter.y);
}
