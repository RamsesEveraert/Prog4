#pragma once
#include "Singleton.h"

#include <vector>

namespace dae
{
	class BoxCollider;
	class CollisionHandler final : public Singleton<CollisionHandler>
	{
	public:
		CollisionHandler() = default;
		virtual ~CollisionHandler() = default;

		CollisionHandler(const CollisionHandler& other) = delete;
		CollisionHandler(CollisionHandler&& other) = delete;
		CollisionHandler& operator=(const CollisionHandler& other) = delete;
		CollisionHandler& operator=(CollisionHandler&& other) = delete;

		void AddCollider(BoxCollider* pCollider);
		void RemoveCollider(BoxCollider* pCollider);

		void Update();
	private:
		bool DoCollide(BoxCollider* pSelf, BoxCollider* pOther) const;

		std::vector<BoxCollider*> m_ColliderPtrs{};
	};
}


