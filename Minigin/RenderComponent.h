#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class TransformComponent;
	class TextureComponent;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(std::weak_ptr<GameObject> owner, const std::string& identifier = "");
		~RenderComponent() = default;

		void Render() override;

	private:
		std::shared_ptr<dae::TransformComponent> m_TransformComponent;
		std::shared_ptr<dae::TextureComponent> m_TextureComponent;
	};
}