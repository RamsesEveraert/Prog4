#pragma once

#include "BaseComponent.h"

#include <memory>
#include <string>


namespace dae
{
	class Font;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() = default;


		void Update(/*float deltaTime*/) override;
		void Render() const override;

		void SetText(const std::string& text);


		// Disabling copy/move constructors and assignment operators   
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		

	private:

		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;

	};
}