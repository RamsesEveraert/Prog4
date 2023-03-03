
#include "GameObject.h"

dae::GameObject::GameObject()
    :m_Components{}, m_MarkedForDelete{ false }, m_pParent{nullptr}
{

}

void dae::GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		if (component)
		component.get()->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		if(component)
		component.get()->Render();
	}
}

void dae::GameObject::MarkForDelete()
{
	m_MarkedForDelete = true;
}

bool dae::GameObject::IsMarkedForDelete() const
{
	return m_MarkedForDelete;
}


void dae::GameObject::SetParent(std::shared_ptr<dae::GameObject> parent, bool keepWorldPosition)
{
    
    auto transformComponent = GetComponent<dae::TransformComponent>();
    auto parentTransformComponent = parent->GetComponent<dae::TransformComponent>();

        if (parent == nullptr)
            transformComponent->SetLocalPosition(transformComponent->GetWorldPosition());
        else
        {
            if (keepWorldPosition)
            {
                transformComponent->SetLocalPosition(transformComponent->GetLocalPosition() - parentTransformComponent->GetWorldPosition());
            }
            
            transformComponent->SetPositionDirty();
        }
       
  
    
}



const std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
    return m_pParent;
}

