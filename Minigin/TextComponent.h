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
	/*class TextComponent final : public BaseComponent
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
	};*/


	/*class TextRendererComponent : public BaseComponent
	{
	public:
		TextRendererComponent(const std::weak_ptr<GameObject>&gameObject, const std::shared_ptr<Font>&font) :
			BaseComponent(gameObject), m_font(font), m_needsUpdate(true)
		{
			m_Texture = nullptr;
		}

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

	private:
		std::shared_ptr<Font> m_font;
		bool m_needsUpdate;
	};*/



	//class TextComponent : public BaseComponent
	//{
	//public:
	//	TextComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& text) :
	//		BaseComponent(gameObject), m_text(text)
	//	{}

	//	void SetText(const std::string& text);

	/*private:
		std::string m_text;
	};



	class FontComponent : public BaseComponent
	{
	public:
		FontComponent(const std::weak_ptr<GameObject>& gameObject, const std::shared_ptr<Font>& font) :
			BaseComponent(gameObject), m_font(font)
		{}

		void SetFont(const std::shared_ptr<Font>& font);

	private:
		std::shared_ptr<Font> m_font;
	};*/


}


