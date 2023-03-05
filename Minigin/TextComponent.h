#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Font;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(std::weak_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> font, const std::string& identifier = "");
		~TextComponent() = default;

		void Update() override;

		void SetText(const std::string& text);

	private:

		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;

	};
}