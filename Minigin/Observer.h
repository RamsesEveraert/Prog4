#pragma once
#include "GameObject.h"

namespace dae
{
	class ObserverInterface
	{
	public:
		virtual ~ObserverInterface() = default;
		virtual void Notify(const GameObject& gameObject/*, Event event*/) = 0;
	};
}

