#pragma once

#include "BaseComponent.h"

#include <string>

namespace dae
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(std::weak_ptr<GameObject> pOwner, const std::string& texturePath, const std::string& identifier = "");
		~TextureComponent() = default;

		void Update() override;

		const std::shared_ptr<Texture2D> GetTexture() const;
		void SetTextureByPath(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

	private:
		std::string m_TexturePath;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}