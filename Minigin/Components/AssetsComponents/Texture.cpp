#include "Texture.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "RenderComponent.h"


dae::Texture::Texture(const std::string& path)
{
	if (path != "") m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
}


const std::shared_ptr<dae::Texture2D> dae::Texture::GetTexture() const
{
	return m_pTexture;
}

void dae::Texture::SetTextureByPath(const std::string& path)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
}

void dae::Texture::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}