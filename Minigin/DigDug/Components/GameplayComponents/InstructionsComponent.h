#pragma once
#include "BaseComponent.h"
namespace dae
{
	class InstructionsComponent final : public BaseComponent
	{
	public:
		InstructionsComponent() = default;
		~InstructionsComponent() = default;

		virtual void RenderImGui() override;
	};

}

