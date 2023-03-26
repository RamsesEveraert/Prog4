#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class Transform;
	class TextureComponent;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		~RenderComponent() = default;

		void Render() override;

	private:
		TextureComponent* m_pTextureComponent;
	};
}