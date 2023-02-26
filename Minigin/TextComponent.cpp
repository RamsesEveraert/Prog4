#include "TextComponent.h"
#include "Renderer.h"

//dae::TextComponent::TextComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& text, std::shared_ptr<Font> font)
//: BaseComponent(gameObject), m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr)
//{
//
//}
//
//void dae::TextComponent::Update()
//{
//	if (m_needsUpdate)
//	{
//		const SDL_Color color = { 255,255,255 }; // only white text is supported now
//		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
//		if (surf == nullptr)
//		{
//			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
//		}
//		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
//		if (texture == nullptr)
//		{
//			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
//		}
//		SDL_FreeSurface(surf);
//		m_textTexture = std::make_shared<Texture2D>(texture);
//		m_needsUpdate = false;
//	}
//}
//
//void dae::TextComponent::SetText(const std::string& text)
//{
//	m_text = text;
//	m_needsUpdate = true;
//}

//void dae::TextRendererComponent::Update(float deltaTime)
//{
//	if (m_needsUpdate)
//	{
//		const SDL_Color color = { 255,255,255 }; // only white text is supported now
//		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
//		if (surf == nullptr)
//		{
//			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
//		}
//		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
//		if (texture == nullptr)
//		{
//			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
//		}
//		SDL_FreeSurface(surf);
//		m_textTexture = std::make_shared<Texture2D>(texture);
//		m_needsUpdate = false;
//	}
//}

//void dae::TextRendererComponent::Render() const
//{
//	dae::BaseComponent::Render();
//}
//
//void dae::FontComponent::SetFont(const std::shared_ptr<Font>& font)
//{
//
//}

//void dae::TextComponent::SetText(const std::string& text)
//{
//	m_text = text;
//	m_needsUpdate = true;
//}
