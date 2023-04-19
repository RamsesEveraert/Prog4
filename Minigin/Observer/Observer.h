#pragma once
#include "GameObject.h"

namespace dae
{
	struct Event;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event) = 0;
	};
}
