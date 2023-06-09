#include <stdexcept>
#include <SDL_pixels.h>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>
#include "imgui_plot.h"
#include "../3rdParty/implot/implot.h"

#include <iostream>




using namespace dae;


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	m_KeyColor = SDL_Color(155, 0, 0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	SceneManager::GetInstance().RenderImGui();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture,  float x,  float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture,  float x,  float y,  float width,  float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& dstRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dstRect);
}

void dae::Renderer::RenderSprite( Texture2D& texture, const SDL_Rect& srcRect, float x,  float y) const
{
	SDL_Rect dstRect{};
	dstRect.x = static_cast<int>(x);
	dstRect.y = static_cast<int>(y);
	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;

	RenderSprite(texture, srcRect, dstRect);
}

void dae::Renderer::RenderSprite( Texture2D& texture, const SDL_Rect& srcRect, float x, float y, float w, float h) const
{
	SDL_Rect dstRect{};
	dstRect.x = static_cast<int>(x);
	dstRect.y = static_cast<int>(y);
	dstRect.w = static_cast<int>(w);
	dstRect.h = static_cast<int>(h);

	RenderSprite(texture, srcRect, dstRect);
}


void Renderer::RenderSprite(Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const 
{
	return m_Renderer; 
}

const SDL_Color& dae::Renderer::GetBackgroundColor() const
{
	return m_ClearColor;
}

void dae::Renderer::SetBackgroundColor(const SDL_Color& color)
{
	m_ClearColor = color;
}

SDL_Window* dae::Renderer::GetSDLWindow() const
{
	return m_Window;
}

