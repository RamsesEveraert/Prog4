#pragma once
#include <SDL.h>
#include "glm/glm.hpp"
#include "Singleton.h"
#include <memory>

namespace dae
{
	class Texture2D;
	class Debugger;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& dstRect) const;

		void RenderSprite(const Texture2D& texture, const SDL_Rect& srcRect, float x, float y) const;
		void RenderSprite(const Texture2D& texture, const SDL_Rect& srcRect, float x, float y, float w, float h) const;
		void RenderSprite(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const;

		SDL_Renderer* GetSDLRenderer() const;

		// basic shape rendering for debugging purpose , possible useful

		void DrawLine(const glm::vec2& start, const glm::vec2& end, const SDL_Color& color) const;

		void DrawRect(const SDL_Rect& rect, const SDL_Color& color) const;

		void DrawCircle(const glm::vec2& center, float radius, const SDL_Color& color) const;

		const SDL_Color& GetBackgroundColor() const;
		void SetBackgroundColor(const SDL_Color& color);

	private:
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};

		

	};
}

