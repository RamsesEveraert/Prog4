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
		RenderComponent(const std::weak_ptr<GameObject>& gameObject);
		~RenderComponent() = default;

		void Update() override;
		void Render() const override;

	private:
		std::shared_ptr<dae::TransformComponent> m_TransformComponent;
		std::shared_ptr<dae::TextureComponent> m_TextureComponent;
	};
}