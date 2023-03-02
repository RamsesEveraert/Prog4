
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

void dae::GameObject::MarkForDelete()
{
	m_MarkedForDelete = true;
}

bool dae::GameObject::IsMarkedForDelete() const
{
	return m_MarkedForDelete;
}

//
//void dae::GameObject::SetParent(std::shared_ptr<dae::GameObject> parent, bool keepWorldPosition)
//{
//    
//       /* if (parent == nullptr)
//            SetLocalPosition(GetWorldPosition());
//        else
//        {
//            if (keepWorldPosition)
//                SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
//            SetPositionDirty()
//        }
//        if (m_parent)
//            m_parent->RemoveChild(this);
//        m_parent = parent;
//        if (m_parent)
//            m_parent->AddChild(this)*/
//  
//    
//}

//void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
//{
//    /* m_localPosition = pos;
//     SetPositionDirty();*/
//}

const std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
    return m_pParent;
}

void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> child)
{
    m_Children.push_back(child);
}

void dae::GameObject::RemoveChild(std::shared_ptr<dae::GameObject> child)
{
    auto it = std::find(m_Children.begin(), m_Children.end(), child);
    if (it != m_Children.end())
    {
        m_Children.erase(it);
    }
}
