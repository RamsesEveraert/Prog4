#pragma once

#include "Component.h"

namespace dae
{
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent();
		virtual ~ColliderComponent();

		virtual void OnCollisionEnter(ColliderComponent* otherCollider);
		virtual void OnCollisionStay(ColliderComponent* otherCollider);
		virtual void OnCollisionExit(ColliderComponent* otherCollider);

		virtual bool IsColliding() const;

	private:
		bool m_IsColliding;
	};
}