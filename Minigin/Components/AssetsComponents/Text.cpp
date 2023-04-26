#include "Text.h"

#include "GameObject.h"

#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Texture.h"
#include "TextureRenderer.h"
#include "ResourceManager.h"


dae::Text::Text()
	: m_NeedsUpdate{true}
	, m_Text{" "}
	, m_pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) }
	, m_TextColor{ 255, 255, 255, 255 } // default to white
	, m_pTexture{}
{

}

void dae::Text::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_TextColor);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		if (GetOwner()->HasComponent<dae::Texture>())
		{
			auto pTexture = std::make_shared<Texture2D>(texture);
			GetOwner()->GetComponent<dae::Texture>()->SetTexture(pTexture);
		}

		if (!GetOwner()->HasComponent<TextureRenderer>())
		{
			GetOwner()->AddComponent<TextureRenderer>();
		}

		m_NeedsUpdate = false;
	}
}

void dae::Text::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::Text::SetFont(std::shared_ptr<Font> font)
{
	m_pFont = std::move(font);
}

void dae::Text::SetTextColor(const SDL_Color& color)
{
	m_TextColor = color;
	m_NeedsUpdate = true;
}



