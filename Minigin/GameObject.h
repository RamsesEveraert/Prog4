#pragma once
#include <memory>
#include "TransformComponent.h"
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
        void Update();
        void FixedUpdate();

        void Render() const;

        void MarkForDelete();
        bool IsMarkedForDelete() const;

        void SetParent(std::weak_ptr<dae::GameObject> pParent, bool keepWorldPosition);
        const std::shared_ptr<GameObject> GetParent() const;

        const int GetChildCount() const;
        const std::shared_ptr<GameObject> GetChildAtIndex(int index) const;
        const std::vector<std::shared_ptr<GameObject>> GetChildren();
        
                
       // extra child methods
        bool IsChild(const std::shared_ptr<GameObject>& pChild) const;
       
        

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
        bool hasComponent() const {
            return GetComponent<T>() != nullptr;
        }

        GameObject();
        ~GameObject() = default;

        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;

    private:

        void AddChild(std::shared_ptr<GameObject> pChild);
        void RemoveChild(std::shared_ptr<GameObject> pChild);

        std::weak_ptr<GameObject> m_pParent; // reference other object

        // momenteel voor vector geopteerd , later zien of unordered map beter is
        std::vector<std::shared_ptr<GameObject>> m_Children;

        std::vector<std::shared_ptr<BaseComponent>> m_Components;
        bool m_MarkedForDelete;

      

    };
}