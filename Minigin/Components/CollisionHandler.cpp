#include "CollisionHandler.h"
#include "BoxCollider.h"

#include <iostream>

void dae::CollisionHandler::AddCollider(BoxCollider* pCollider)
{
	m_ColliderPtrs.emplace_back(pCollider);
}

void dae::CollisionHandler::RemoveCollider(BoxCollider* pCollider)
{
	if (m_ColliderPtrs.empty()) return;

	m_ColliderPtrs.erase(std::remove(begin(m_ColliderPtrs), end(m_ColliderPtrs), pCollider), end(m_ColliderPtrs));
}


void dae::CollisionHandler::Update()
{
	bool hasBeenHit{};
	for (auto pSelf : m_ColliderPtrs)
	{
		for (auto pOther : m_ColliderPtrs)
		{
			if (pSelf == pOther) continue;
			if (DoCollide(pSelf, pOther) && !hasBeenHit)
			{
				hasBeenHit = true;
				pSelf->Hit(pOther);
			}
		}
	}
}


bool dae::CollisionHandler::DoCollide(BoxCollider* pSelf, BoxCollider* pOther) const
{
	const glm::vec2 colliderCenter{ pSelf->GetCenterPosition() };
	const glm::vec2 otherCenter{ pOther->GetCenterPosition() };

	const glm::vec2 colliderHalfSize{ pSelf->GetSize().x * 0.5f, pSelf->GetSize().y * 0.5f };
	const glm::vec2 otherHalfSize{ pOther->GetSize().x * 0.5f, pOther->GetSize().y * 0.5f };

	// distance between the center positions of the colliders
	const glm::vec2 distance{ glm::abs(colliderCenter - otherCenter) };

	// minimum distance no overlap
	const glm::vec2 minDistance{ colliderHalfSize + otherHalfSize };

	return (distance.x < minDistance.x && distance.y < minDistance.y);

}
