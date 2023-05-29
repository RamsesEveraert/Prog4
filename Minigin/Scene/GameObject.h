#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include <utility>

namespace dae
{
    class Texture2D;
    class Transform;
    class Component;
    class GameObject final : public std::enable_shared_from_this<GameObject>
    {
    public:

        const std::string& GetObjectName() const;

        void InitGameObject();

        /* GameObject* CreateGameObject(Scene* pScene, const std::string& objectName);*/

         // updating

        void Update();
        void FixedUpdate();

        // rendering

        void Render() const;
        void RenderImGui();

        // transform 
        Transform* GetTransform()const;
        glm::vec2 GetSpriteCenterPoint();

        // parent and children

        void SetParent(GameObject* pNewParent, bool keepWorldPosition);
        GameObject* GetParent() const;

        const int GetChildCount() const;
        const std::shared_ptr<GameObject> GetChildAtIndex(int index) const;
        std::vector<std::shared_ptr<GameObject>> GetChildren();

        bool IsChild(const std::shared_ptr<GameObject>& pChild) const;

        // components

       
        template<class T, typename... Args>
        T* AddComponent(Args&&... args);
        template<class T>
        inline bool removeComponent();
        template<class T>
        T* GetComponent() const;
        template<class T>
        std::vector<T*> GetAllInstancesOfComponent() const;
        template<class T>
        bool HasComponent() const;

        // cleanup

        void MarkForDelete();
        bool IsMarkedForDelete() const;

        explicit GameObject(const std::string& objectName);
        ~GameObject() = default;

        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;

    private:

        const std::string m_NameObject;

        //Player
        void InitPlayer();

        //Transform
        bool m_IsTransformDirty;

        Transform* m_pTransform;

        // child parents

        void AddChild(std::shared_ptr<GameObject> pChild);
        void RemoveChild(std::shared_ptr<GameObject> pChild);

        GameObject* m_pParent;

        // momenteel voor vector geopteerd , later zien of unordered map beter is -> unordermap pakken
        std::vector<std::shared_ptr<GameObject>> m_Children;

        // cleanup
        bool m_MarkedForDelete;

        // components
        std::vector<std::unique_ptr<Component>> m_Components;
    };

#pragma region TemplateFunctions

  
    template<class T, typename... Args>
    inline T* GameObject::AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>(), "Component is NOT derived from the ComponentBase class");

        auto pComponent = std::make_unique<T>(std::forward<Args>(args)...);
        T* returnComponentPtr = pComponent.get();

        // automatically make owner of components
        pComponent->SetOwner(this);

        m_Components.push_back(std::move(pComponent));

        return returnComponentPtr;
    }

    template<class T>
    inline bool GameObject::removeComponent() {
        static_assert(!std::is_same<Transform, T>(), "Transform component cannot be removed");
        static_assert(std::is_base_of<Component, T>(), "Component is NOT derived from the ComponentBase class");

        for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
        {
            if (auto* pComponent = dynamic_cast<T*>(it->get())) {
                m_Components.erase(it);
                return true;
            }
        }
        return false;
    }

    template<class T>
    inline T* GameObject::GetComponent() const {
        static_assert(std::is_base_of<Component, T>(), "Component is NOT derived from the ComponentBase class");

        for (const auto& pComponent : m_Components)
        {
            T* derivedComponent{ dynamic_cast<T*>(pComponent.get()) };
            if (derivedComponent) return derivedComponent;
        }

        return nullptr;
    }

    template<class T>
    inline std::vector<T*> GameObject::GetAllInstancesOfComponent() const {
        static_assert(std::is_base_of<Component, T>(), "Component is NOT derived from the ComponentBase class");

        std::vector<T*> pComponents{};

        for (const auto& pComponent : m_Components)
        {
            T* derivedComponent{ dynamic_cast<T*>(pComponent.get()) };
            if (derivedComponent) pComponents.push_back(derivedComponent);
        }

        return pComponents;
    }

    template<class T>
    inline bool GameObject::HasComponent() const
    {
        static_assert(std::is_base_of<Component, T>(), "Component is NOT derived from the ComponentBase class");

        if (!this) return false;

        for (auto& component : m_Components)
        {
            if (!component) continue;

            T* derivedComponent = dynamic_cast<T*>(component.get());
            if (derivedComponent) return true;
        }
        return false;
    }

#pragma endregion
}

