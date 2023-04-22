#include "Text.h"

#include "GameObject.h"

#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Texture.h"
#include "RenderComponent.h"


dae::Text::Text()
	: m_NeedsUpdate{true}
	, m_Text{}
	, m_pFont{}
{
}

void dae::Text::Update()
{

	/*if (!m_pTextureRenderer)
	{
		m_pTextureRenderer = GetOwner()->GetComponent<TextureRenderer>();

		if (!m_pTextureRenderer)
		{
			Logger::LogWarning("The owner of this TextComponent component has no TextureRenderer", GetOwner());
			return false;
		}
	}*/

	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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

		;
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