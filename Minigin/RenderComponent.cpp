#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject)
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	if (auto gameObject = m_gameObject.lock())  //  checks if the game object associated with this RenderComponent instance still exists.
	{
		auto transformComp = gameObject->GetComponent<dae::TransformComponent>(); // check if there is a transform component
		if (!transformComp)
			return;

		const auto& pos = transformComp->getPosition();

		
		if (auto texture = gameObject->GetComponent<dae::TextureComponent>()->GetTexture()) // checks if there is a texture component + texture
		{
			Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
		}
	}
}
