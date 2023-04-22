#include "TextureRenderer.h"

#include "GameObject.h"
#include "Texture.h"
#include "Transform.h"

#include "Renderer.h"

dae::TextureRenderer::TextureRenderer()
	: m_pTexture{}
{
}

void dae::TextureRenderer::Render()
{
	CheckTexture();
	if (!m_pTexture) return;
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();

	auto texture = m_pTexture->GetTexture();
	Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
}

void dae::TextureRenderer::CheckTexture()
{
	auto owner = GetOwner();
	if (owner->HasComponent<Texture>()) m_pTexture = owner->GetComponent<Texture>();
	if (!m_pTexture)
	{
		std::cout << "owner: " << owner << " Has no texture\n";
	}
}
