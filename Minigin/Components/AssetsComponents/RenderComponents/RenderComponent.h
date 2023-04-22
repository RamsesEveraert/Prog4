#pragma once

#include "Component.h"

namespace dae
{
	class RenderComponent  : public Component
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		virtual void Render();
	};
}