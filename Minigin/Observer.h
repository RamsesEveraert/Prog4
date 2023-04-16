#pragma once
#include "GameObject.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& gameObject/*, Event event*/) = 0;
	};
}
