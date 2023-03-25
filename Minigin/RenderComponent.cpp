#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent(std::weak_ptr<GameObject> pOwner, const std::string& identifier)
	: BaseComponent(pOwner, identifier),  m_TextureComponent{ nullptr }
{
	auto owner = pOwner.lock();

	if (owner->HasComponent<dae::TextureComponent>())
	{
		m_TextureComponent = owner->GetComponent<dae::TextureComponent>();
	}
}

void dae::RenderComponent::Render()


{
	if (!GetOwner())
		return;

	if (m_TextureComponent)
	{
		auto pos = GetOwner()->GetWorldPosition();

		auto texture = m_TextureComponent->GetTexture();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}

}