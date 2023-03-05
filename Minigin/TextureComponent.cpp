#include "TextureComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

dae::TextureComponent::TextureComponent(std::weak_ptr<GameObject> pOwner, const std::string& texturePath , const std::string& identifier)
	: BaseComponent(pOwner,identifier), m_pTexture(nullptr)
{
	if (texturePath != "")
		m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
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