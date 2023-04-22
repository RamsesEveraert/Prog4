#include "Sprite.h"

#include "Renderer.h"
#include "Texture.h"

#include "ResourceManager.h"

using namespace dae;

dae::Sprite::Sprite(const std::string& spritePath, const SDL_Rect& spriteSrc, float scale)
	: m_pTexture{ ResourceManager::GetInstance().LoadTexture(spritePath) }, m_SrcRect{ spriteSrc }, m_Position{ 0, 0 },
	m_Size{ spriteSrc.w, spriteSrc.h }, m_Color{ }, m_Alpha{},
	m_Flip{ SDL_FLIP_NONE }, m_Angle{ }, m_Scale{scale}
{
}

void dae::Sprite::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}

const glm::vec2& dae::Sprite::GetPosition() const
{
	return m_Position;
}

void dae::Sprite::SetSize(int width, int height)
{
	m_Size = { width, height };
}

glm::ivec2 dae::Sprite::GetSize() const
{
	return m_Size;
}

void dae::Sprite::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

const SDL_Color& dae::Sprite::GetColor() const
{
	return m_Color;
}

void dae::Sprite::SetAlpha(Uint8 alpha)
{
	m_Alpha = alpha;
}

Uint8 dae::Sprite::GetAlpha() const
{
	return m_Alpha;
}

void dae::Sprite::SetFlip(const SDL_RendererFlip& flip)
{
	m_Flip = flip;
}

const SDL_RendererFlip& dae::Sprite::GetFlip() const
{
	return m_Flip;
}

void dae::Sprite::SetRotation(float angle)
{
	m_Angle = angle;
}

float dae::Sprite::GetRotation() const
{
	return m_Angle;
}

void dae::Sprite::SetSpriteSrc(const SDL_Rect& spriteSrc)
{
	m_SrcRect = spriteSrc;
}

const SDL_Rect& dae::Sprite::GetSpriteSrc() const
{
	return m_SrcRect;
}

void dae::Sprite::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
}

const glm::vec2& dae::Sprite::GetScale() const
{
	return m_Scale;
}

void dae::Sprite::SetTexture(const std::string& path)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
}

 const std::shared_ptr<dae::Texture2D> dae::Sprite::GetTexture() const
{
	return m_pTexture;
}

