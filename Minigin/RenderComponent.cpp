#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent()
	: m_pTextureComponent{ nullptr }
{
}

void dae::RenderComponent::Render()
{
	if (!m_pTextureComponent)
	{
		m_pTextureComponent = GetOwner()->GetComponent<TextureComponent>();

		if (!m_pTextureComponent)
		{
			std::cout << "No TextureComponent found! \n";
			return;
		}
	}

	if (!GetOwner())
		return;

	if (m_pTextureComponent)
	{
		auto pos = GetOwner()->GetWorldPosition();

		auto texture = m_pTextureComponent->GetTexture();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}

}