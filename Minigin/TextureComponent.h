#pragma once

#include "BaseComponent.h"

#include <memory>
#include <string>




namespace dae
{
	class Texture2D;
	class TextureComponent final: public BaseComponent
	{
	public:
		TextureComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& texturePath);
		~TextureComponent() = default;

		void Update(/*float deltaTime*/) override;
		void Render() const override;

		const std::shared_ptr<Texture2D> GetTexture() const;
		void SetTextureByPath(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

		// Disabling copy/move constructors and assignment operators   
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

	private:
		std::string m_TexturePath;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}