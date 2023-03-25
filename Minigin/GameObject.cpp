
#include "GameObject.h"
#include "SceneManager.h"
#include "Transform.h"
#include "BaseComponent.h"

using namespace dae;

const std::string& dae::GameObject::GetObjectName() const
{
    return m_NameObject;
}

dae::GameObject::GameObject(const std::string& objectName)
    : m_Components{} 
    , m_pParent{ nullptr }
    , m_MarkedForDelete{ false }
    , m_IsTransformDirty{ true }
    , m_TransformComponent{}
    , m_Children {}
    , m_NameObject{ objectName }
{
}

void dae::GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		if (component)
		component->Update();
	}

    for (const auto& child : m_Children)
    {
        if (child)
            child->Update();
    }

    if (m_IsTransformDirty)
        UpdateWorldPos();


}
void dae::GameObject::FixedUpdate()
{
    for (auto& component : m_Components)
    {
        if (component)
            component->FixedUpdate();
    }
    for (const auto& child : m_Children)
    {
        if (child)
            child->FixedUpdate();
    }
}
void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		if(component)
		component->Render();
	}
    for (const auto& child : m_Children)
    {
        if (child)
            child->Render();
    }
}

void dae::GameObject::RenderImGui()
{
    for (const auto& component : m_Components)
    {
        if (component)
            component->RenderImGui();
    }
    for (const auto& child : m_Children)
    {
        if (child)
            child->RenderImGui();
    }
}

void dae::GameObject::SetParent(GameObject* pNewParent, bool keepWorldPosition)
{
        if (m_pParent == pNewParent)
        {
            return;
        }

        //Remove itself as a child from the previous parent
        if (m_pParent)
        {
            m_pParent->RemoveChild(shared_from_this());
        }

        m_pParent = pNewParent;

        //Update position
        if (m_pParent == nullptr)
        {
            //Local position is now world position
            const auto position{ m_TransformComponent.GetWorldPosition() };
            SetPosition(position.x, position.y);
        }
        else
        {
            //Add itself as a child to the given parent
            m_pParent->AddChild(shared_from_this());

            if (keepWorldPosition)
            {
                const auto position{ m_TransformComponent.GetLocalPosition() - m_pParent->GetWorldPosition() };
                SetPosition(position.x, position.y);
            }
            else
            {
                //Recalculate world position
                SetTransformDirty();
            }
        }
    
   
}


GameObject* dae::GameObject::GetParent() const
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

const std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAtIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_Children.size()))
    {
        return nullptr;
    }
    return m_Children[index];
}

const std::vector<std::shared_ptr<dae::GameObject>> dae::GameObject::GetChildren()
{
    return m_Children;
}

// extra methods

bool dae::GameObject::IsChild(const std::shared_ptr<GameObject>& pChild) const
{
    auto it = std::find(m_Children.begin(), m_Children.end(), pChild);
    return (it != m_Children.end());
}


void dae::GameObject::UpdateWorldPos()
{
        m_IsTransformDirty = false;

        if (m_pParent)
        {
            m_TransformComponent.UpdateWorldPosition(m_TransformComponent.GetLocalPosition() + m_pParent->GetWorldPosition());
        }
        else
        {
            m_TransformComponent.UpdateWorldPosition(m_TransformComponent.GetLocalPosition());
        }
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
   return m_TransformComponent.GetWorldPosition();
}

glm::vec3 dae::GameObject::GetLocalPosition() const
{
   return m_TransformComponent.GetLocalPosition();
}

//int dae::GameObject::GetPriority() const
//{
//    return m_Priority;
//}

void dae::GameObject::SetTransformDirty()
{
    m_IsTransformDirty = true;

    for (const auto& pChild : m_Children)
    {
        pChild->SetTransformDirty();
    }
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
        SetTransformDirty();
        m_TransformComponent.SetLocalPosition(glm::vec3(x, y, z));
}

void dae::GameObject::SetPosition(const glm::vec3& pos)
{
        SetTransformDirty();
        m_TransformComponent.SetLocalPosition(pos);
}

