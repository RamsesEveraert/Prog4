#pragma once
#include "GameObject.h"

namespace dae
{
	class Event;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event) = 0;
	};
}
