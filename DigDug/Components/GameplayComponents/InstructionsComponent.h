#pragma once
#include "Component.h"
namespace dae
{
	class InstructionsComponent final : public Component
	{
	public:
		InstructionsComponent() = default;
		~InstructionsComponent() = default;

		virtual void RenderImGui() override;
	};

}

