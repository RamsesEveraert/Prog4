#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::RenderComponent::RenderComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject), m_TransformComponent {nullptr}, m_TextureComponent{nullptr}
{

	/*if (gameObject.lock()->hasComponent<dae::TransformComponent>())
	{
		m_TransformComponent = gameObject.lock()->GetComponent<dae::TransformComponent>();
	}

	if (gameObject.lock()->hasComponent<dae::TextureComponent>())
	{
		m_TextureComponent = gameObject.lock()->GetComponent<dae::TextureComponent>();
	}*/
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const

// zie feedback over cache component in initialisation
// zie feedabck over render
{
	if (auto gameObject = m_Parent.lock())  //  checks if the game object associated with this RenderComponent instance still exists.
	{
		auto transformComp = gameObject->GetComponent<dae::TransformComponent>(); // checks if there is a transform component
		if (!transformComp)
			return;

		const auto& pos = transformComp->GetPosition();

		
		if (auto texture = gameObject->GetComponent<dae::TextureComponent>()->GetTexture()) // checks if there is a texture component + texture
		{
			Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
		}
	}
}
