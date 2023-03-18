#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent(std::weak_ptr<GameObject> pOwner, const std::string& identifier)
	: BaseComponent(pOwner, identifier), m_TransformComponent{ nullptr }, m_TextureComponent{ nullptr }
{
	auto owner = pOwner.lock();
	if (owner->hasComponent<dae::TransformComponent>())
	{
		m_TransformComponent = owner->GetComponent<dae::TransformComponent>();
	}

	if (owner->hasComponent<dae::TextureComponent>())
	{
		m_TextureComponent = owner->GetComponent<dae::TextureComponent>();
	}
}

void dae::RenderComponent::Render()


{
	if (!GetOwner())
		return;

	if (!m_TransformComponent)
		return;

	const auto& pos = m_TransformComponent->GetWorldPosition();

	if (m_TextureComponent)
	{
		auto texture = m_TextureComponent->GetTexture();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}

}