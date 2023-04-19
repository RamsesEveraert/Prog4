#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Font;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent();
		~TextComponent() = default;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);

	private:

		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;

	};
}