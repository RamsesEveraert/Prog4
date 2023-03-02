#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent(const std::weak_ptr<GameObject>& parent)
	: BaseComponent(parent), m_TransformComponent {}, m_TextureComponent{}
{

	if (parent.lock()->HasComponent<dae::TransformComponent>())
	{
		m_TransformComponent = parent.lock()->GetComponent<dae::TransformComponent>();
	}

	if (parent.lock()->HasComponent<dae::TextureComponent>())
	{
		m_TextureComponent = parent.lock()->GetComponent<dae::TextureComponent>();
	}
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	if (!GetOwner().lock())
		return;

	if (!m_TransformComponent.lock())
		return;

	const auto& pos = m_TransformComponent.lock()->GetPosition();

	if (m_TextureComponent.lock())
	{
		auto texture = m_TextureComponent.lock()->GetTexture();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}

}
