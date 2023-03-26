#include "TextureComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "RenderComponent.h"

dae::TextureComponent::TextureComponent()
	: m_pTexture(nullptr)
{
}

void dae::TextureComponent::Update()
{
	//TODO later
}

const std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture() const
{
	return m_pTexture;
}

void dae::TextureComponent::SetTextureByPath(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}