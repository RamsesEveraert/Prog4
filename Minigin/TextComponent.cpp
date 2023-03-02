#include "TextComponent.h"

#include "GameObject.h"

#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "RenderComponent.h"


dae::TextComponent::TextComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& text, std::shared_ptr<Font> font)
	: BaseComponent(gameObject), m_NeedsUpdate(true), m_Text(text), m_Font(std::move(font))
{
}

void dae::TextComponent::Update()
{
		if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
		if (GetParent()->hasComponent<dae::TextureComponent>())
		{
			auto pTexture = std::make_shared<Texture2D>(texture);
			GetParent()->GetComponent<dae::TextureComponent>()->SetTexture(pTexture);
		}
		
		;
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
