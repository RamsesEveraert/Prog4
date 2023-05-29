#include "GameObject.h"
#include "SceneManager.h"

#include "Transform.h"
#include "MovementComponent.h"
#include "Sprite.h"
#include "CollisionHandler.h"
#include "BoxCollider.h"


#include <regex>

using namespace dae;



dae::GameObject::GameObject(const std::string& objectName)
    : m_Components{}
    , m_pParent{ nullptr }
    , m_MarkedForDelete{ false }
    , m_IsTransformDirty{ true }
    , m_pTransform{}
    , m_Children{}
    , m_NameObject{ objectName }
{
    InitGameObject();
}

const std::string& dae::GameObject::GetObjectName() const
{
    return m_NameObject;
}

void dae::GameObject::InitGameObject()
{
    m_pTransform = AddComponent<Transform>();
    m_pTransform->SetPosition(glm::vec2(0, 0));
}

void dae::GameObject::Update()
{
    for (const auto& component : m_Components)
    {
        if (component)
            component->Update();
        //if (HasComponent<BoxCollider>()) dae::CollisionHandler::GetInstance().Update();
    }

    for (const auto& child : m_Children)
    {
        if (child)
            child->Update();
    }

    if (m_pTransform->IsDirty())
    {
        m_pTransform->UpdateWorldPosition();
        if (HasComponent<Sprite>()) GetComponent<Sprite>()->SetPosition(m_pTransform->GetWorldPosition()); // update sprite position after object position change
        std::cout << "position changed \n";
    }
       


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
        if (component)
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
        const auto position{ m_pTransform->GetWorldPosition() };
        m_pTransform->SetPosition(position.x, position.y);
    }
    else
    {
        //Add itself as a child to the given parent
        m_pParent->AddChild(shared_from_this());

        if (keepWorldPosition)
        {
            const auto position{ m_pTransform->GetLocalPosition() - m_pParent->GetTransform()->GetWorldPosition() };
            m_pTransform->SetPosition(position.x, position.y);
        }
        else
        {
            //Recalculate world position
            m_pTransform->SetDirty();
        }
    }


}
GameObject* dae::GameObject::GetParent() const
{
    return m_pParent;
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
    return static_cast<int>(m_Children.size());
}
const std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAtIndex(int index) const
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
bool dae::GameObject::IsChild(const std::shared_ptr<GameObject>& pChild) const
{
    auto it = std::find(m_Children.begin(), m_Children.end(), pChild);
    return (it != m_Children.end());
}

Transform* dae::GameObject::GetTransform() const
{
    const auto transform = GetComponent<Transform>();
    return transform ? transform : nullptr;
}

glm::vec2 dae::GameObject::GetSpriteCenterPoint()
{
    if (!HasComponent<Sprite>()) return glm::vec2{}; // no sprite no need for this function
    const glm::vec2 spritePosition{ m_pTransform->GetWorldPosition() };
    const glm::vec2 spriteScale{ 1.5f,1.5f };
    const glm::vec2 spriteSize{GetComponent<Sprite>()->GetSize() };
    const glm::vec2 spriteCenter{ spritePosition + spriteSize * 0.5f };

    return spriteCenter;
}

void dae::GameObject::MarkForDelete()
{
    m_MarkedForDelete = true;
}
bool dae::GameObject::IsMarkedForDelete() const
{
    return m_MarkedForDelete;
}
