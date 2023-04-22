#include "SpriteRenderer.h"

#include "GameObject.h"

#include "Sprite.h"
#include "Transform.h"

#include "Renderer.h"

dae::SpriteRenderer::SpriteRenderer()
	: m_pSprite{}
{
	
}

void dae::SpriteRenderer::Render()
{
	CheckSprite();
	if (!m_pSprite) return;

	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	auto scale = m_pSprite->GetScale();

	auto texture = m_pSprite->GetTexture();
	auto srcRect = m_pSprite->GetSpriteSrc();
	SDL_Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(srcRect.w * scale.x), static_cast<int>(srcRect.h * scale.y) };

	Renderer::GetInstance().RenderSprite(*texture, srcRect, dstRect);
}

void dae::SpriteRenderer::CheckSprite()
{
	auto owner = GetOwner();
	if (owner->HasComponent<Sprite>()) m_pSprite = owner->GetComponent<Sprite>();
	if (!m_pSprite)
	{
		std::cout << "owner: " << owner << " Has no sprite \n";
	}
}
