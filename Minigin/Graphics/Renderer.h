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

		void RenderSprite( Texture2D& texture, const SDL_Rect& srcRect, float x, float y) const;
		void RenderSprite( Texture2D& texture, const SDL_Rect& srcRect, float x, float y, float w, float h) const;
		void RenderSprite( Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const;
		void SetBackgroundColor(const SDL_Color& color);

		SDL_Window* GetSDLWindow() const;

	private:

		SDL_Color m_KeyColor;

		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_ClearColor{};

		

	};
}

