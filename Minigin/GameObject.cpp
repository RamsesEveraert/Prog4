
#include "GameObject.h"

dae::GameObject::GameObject()
    :m_Components{}, m_MarkedForDelete{ false }, m_pParent{nullptr}, m_Children{}
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

void dae::GameObject::SetParent(std::shared_ptr<dae::GameObject> pParent, bool keepWorldPosition)
{
    if (m_pParent == pParent)
    {
        return;
    }

    auto transformComponent = GetComponent<dae::TransformComponent>();
    auto parentTransformComponent = pParent ? pParent->GetComponent<dae::TransformComponent>() : nullptr;

    if (!pParent)
    {
        transformComponent->SetLocalPosition(transformComponent->GetWorldPosition());
    }
    else
    {
        if (keepWorldPosition)
        {
            transformComponent->SetLocalPosition(transformComponent->GetLocalPosition() - parentTransformComponent->GetWorldPosition());
        }

        transformComponent->SetPositionDirty();
    }

    if (m_pParent)
    {
        m_pParent->RemoveChild(shared_from_this());
    }

    m_pParent = pParent;

    if (m_pParent)
    {
        m_pParent->AddChild(shared_from_this());
    }
}


const std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
    return m_pParent;
}



void dae::GameObject::MarkForDelete()
{
    m_MarkedForDelete = true;
}
bool dae::GameObject::IsMarkedForDelete() const
{
    return m_MarkedForDelete;
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> pChild)
{
     for (const auto& child : m_Children)
    {
        if (child == pChild)
            return;
    }

    m_Children.push_back(pChild);
}
void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
    auto it = std::find(m_Children.begin(), m_Children.end(), pChild);
    if (it != m_Children.end())
    {
        m_Children.erase(it);
    }
}

const int dae::GameObject::GetChildCount() const
{
    return static_cast<int>( m_Children.size());
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAtIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_Children.size()))
    {
        return nullptr;
    }
    return m_Children[index];
}

std::vector<std::shared_ptr<dae::GameObject>> dae::GameObject::GetChildren()
{
    return m_Children;
}

// extra methods

bool dae::GameObject::IsChild(const std::shared_ptr<GameObject>& pChild) const
{
    auto it = std::find(m_Children.begin(), m_Children.end(), pChild);
    return (it != m_Children.end());
}



