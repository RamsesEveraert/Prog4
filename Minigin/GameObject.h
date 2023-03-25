#pragma once

#include "Transform.h"

#include <memory>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

namespace dae
{
    class Texture2D;
    class BaseComponent;

    class GameObject final : public std::enable_shared_from_this<GameObject>
    {
    public:

        const std::string& GetObjectName() const;

        // updating

        void Update();
        void FixedUpdate();

        // rendering

        void Render() const;
        void RenderImGui();

        // transform 

        void SetPosition(float x, float y, float z = 0);
        void SetPosition(const glm::vec3& pos);

        glm::vec3 GetWorldPosition();
        glm::vec3 GetLocalPosition() const;

        // parenting

        void SetParent(GameObject* pNewParent, bool keepWorldPosition);
        GameObject* GetParent() const;

        const int GetChildCount() const;
        const std::shared_ptr<GameObject> GetChildAtIndex(int index) const;
        const std::vector<std::shared_ptr<GameObject>> GetChildren();
        
                
       // extra child methods
        bool IsChild(const std::shared_ptr<GameObject>& pChild) const;
       
        // components

        template<typename T>
        std::shared_ptr<T> AddComponent(std::shared_ptr<T> component) {

            m_Components.push_back(component);
            return component;
        }

        template<typename T>
        void removeComponent(std::shared_ptr<T> componentToRemove = nullptr) {
            auto componentsToRemove = std::vector<std::shared_ptr<BaseComponent>>{};
            auto componentType = std::dynamic_pointer_cast<T>(nullptr);
            for (auto& component : m_Components)
            {
                componentType = std::dynamic_pointer_cast<T>(component);
                if (componentType)
                {
                    if (componentToRemove == nullptr || componentType == componentToRemove)
                    {
                        componentsToRemove.push_back(component);
                    }
                }
            }

            for (auto& component : componentsToRemove)
            {
                m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
            }
        }


        template<typename T>
        std::shared_ptr<T> GetComponent(const std::string& identifier = "") const {
            for (const auto& component : m_Components) {
                if (std::shared_ptr<T> pointerType = std::dynamic_pointer_cast<T>(component)) {
                    // Check if the component's identifier matches the requested identifier
                    if (pointerType->GetIdentifier() == identifier) {
                        return pointerType;
                    }
                }
            }
            return nullptr;
        }


        

        template<typename T>
        std::vector<std::shared_ptr<T>> GetAllInstancesOfComponent() const {
            std::vector<std::shared_ptr<T>> components;
            for (const auto& component : m_Components) {
                if (std::shared_ptr<T> pointerType = std::dynamic_pointer_cast<T>(component)) {
                    components.push_back(pointerType);
                }
            }
            return components;
        }



        template<typename T>
      constexpr bool HasComponent() const {
            return GetComponent<T>() != nullptr;
        }


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

        //Transform
        void UpdateWorldPos();
        void SetTransformDirty();
        bool m_IsTransformDirty;

        TransformComponent m_TransformComponent;

        // child parents

        void AddChild(std::shared_ptr<GameObject> pChild);
        void RemoveChild(std::shared_ptr<GameObject> pChild);

        GameObject* m_pParent; // reference other object

        // momenteel voor vector geopteerd , later zien of unordered map beter is -> unordermap pakken
        std::vector<std::shared_ptr<GameObject>> m_Children;

        // components
        std::vector<std::shared_ptr<BaseComponent>> m_Components;

        // cleanup
        bool m_MarkedForDelete;      

    };
}