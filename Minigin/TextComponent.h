#pragma once
#include <memory>
#include <stdexcept>
#include <SDL_ttf.h>
#include <string>

#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:

		void Update();
		void SetText(const std::string& text);

		TextComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}


