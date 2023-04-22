#include "Texture.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "RenderComponent.h"


dae::Texture::Texture()
	: m_pTexture{}
{
}


const std::shared_ptr<dae::Texture2D> dae::Texture::GetTexture() const
{
	return m_pTexture;
}

void dae::Texture::SetTextureByPath(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::Texture::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}