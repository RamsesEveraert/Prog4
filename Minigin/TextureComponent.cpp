#include "TextureComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

dae::TextureComponent::TextureComponent(const std::weak_ptr<GameObject>& gameObject, const std::string& texturePath)
	: BaseComponent(gameObject), m_pTexture(nullptr)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void dae::TextureComponent::Update(/*float deltaTime*/)
{
}

void dae::TextureComponent::Render() const
{
	m_gameObject.lock()->GetComponent<dae::RenderComponent>()->Render();

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
