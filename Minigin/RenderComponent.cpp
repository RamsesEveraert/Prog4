#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject), m_TransformComponent{ nullptr }, m_TextureComponent{ nullptr }
{

	if (gameObject.lock()->hasComponent<dae::TransformComponent>())
	{
		m_TransformComponent = gameObject.lock()->GetComponent<dae::TransformComponent>();
	}

	if (gameObject.lock()->hasComponent<dae::TextureComponent>())
	{
		m_TextureComponent = gameObject.lock()->GetComponent<dae::TextureComponent>();
	}
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const


{

	if (!GetOwner())
		return;

	if (!m_TransformComponent)
		return;

	const auto& pos = m_TransformComponent->GetPosition();

	if (m_TextureComponent)
	{
		auto texture = m_TextureComponent->GetTexture();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}

}