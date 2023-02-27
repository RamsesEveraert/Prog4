#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(const std::weak_ptr<GameObject>& gameObject);
		~RenderComponent() = default;

		void Update() override;
		void Render() const override;

	private:
	};
}