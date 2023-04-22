#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>
#include "imgui_plot.h"
#include "../3rdParty/implot/implot.h"


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
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	SceneManager::GetInstance().RenderImGui();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
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

void dae::Renderer::RenderSprite(const Texture2D& texture, const SDL_Rect& srcRect, float x,  float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = srcRect.w;
	dst.h = srcRect.h;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst);
}

void dae::Renderer::RenderSprite(const Texture2D& texture, const SDL_Rect& srcRect, float x, float y, float w, float h) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(w);
	dst.h = static_cast<int>(h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst);
}

void dae::Renderer::RenderSprite(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const 
{
	return m_renderer; 
}

void Renderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(m_renderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
}

void Renderer::DrawRect(const SDL_Rect& rect, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_renderer, &rect);
}

void dae::Renderer::DrawCircle(const glm::vec2& center, float radius, const SDL_Color& color) const
{
	// bron: https://iq.opengenus.org/bresenhams-circle-drawing-algorithm
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	int x = 0;
	int y = static_cast<int>(radius);
	int d = 3 - 2 * static_cast<int>(radius);

	int cx = static_cast<int>(center.x);
	int cy = static_cast<int>(center.y);

	while (x <= y)
	{
		SDL_RenderDrawPoint(m_renderer, cx + x, cy + y);
		SDL_RenderDrawPoint(m_renderer, cx - x, cy + y);
		SDL_RenderDrawPoint(m_renderer, cx + x, cy - y);
		SDL_RenderDrawPoint(m_renderer, cx - x, cy - y);
		SDL_RenderDrawPoint(m_renderer, cx + y, cy + x);
		SDL_RenderDrawPoint(m_renderer, cx - y, cy + x);
		SDL_RenderDrawPoint(m_renderer, cx + y, cy - x);
		SDL_RenderDrawPoint(m_renderer, cx - y, cy - x);

		if (d < 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}
const SDL_Color& dae::Renderer::GetBackgroundColor() const
{
	return m_clearColor;
}

void dae::Renderer::SetBackgroundColor(const SDL_Color& color)
{
	m_clearColor = color;
}
