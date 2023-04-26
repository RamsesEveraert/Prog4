#pragma once

#include "Component.h"
#include <SDL_ttf.h>
#include <SDL.h>


namespace dae
{
	class Font;
	class Texture;
	class Text final : public Component
	{
	public:
		Text();
		~Text() = default;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);

		void SetTextColor(const SDL_Color& color);

	private:

		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		SDL_Color m_TextColor;
		Texture* m_pTexture;

	};
}