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

	class GameObject final
	{
	public:
		void Update();
		void Render() const;

        void MarkForDelete();
        bool IsMarkedForDelete() const;

        void SetParent(std::shared_ptr<dae::GameObject> parent, bool keepWorldPosition);
        const std::shared_ptr<dae::GameObject> GetParent() const;
        
        void AddChild(std::shared_ptr<dae::GameObject> child);
        void RemoveChild(std::shared_ptr<dae::GameObject> child);


        template<typename T>
        std::weak_ptr<T> AddComponent(std::weak_ptr<T> component)  // weak pointers: owner is gemaakt in main.cpp dit is een reference als allemaal owners zijn is het shared pointer
        {
            m_Components.push_back(component);
            return component.lock;
        }

        template<typename T>
        void RemoveComponent() 
        {
            auto it = std::find_if(m_Components.begin(), m_Components.end(), [](const std::shared_ptr<BaseComponent>& component) {
                return dynamic_cast<T*>(component.get()) != nullptr;
                });
            if (it != m_Components.end()) {
                m_Components.erase(it);
            }
        }

        template<typename T>
        std::weak_ptr<T> GetComponent() const
        {
            for (const auto& component : m_Components) {
                if (std::shared_ptr<T> sharedPtr = std::dynamic_pointer_cast<T>(component.lock())) {
                    return std::weak_ptr<T>(sharedPtr);
            }
            return std::weak_ptr<T>();
            
        }


        template<typename T>
        bool HasComponent() const {
            return GetComponent<T>() != nullptr;
        }


		GameObject();
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

        std::shared_ptr<GameObject> m_pParent;
        std::vector<std::shared_ptr<GameObject>> m_Children;

		std::vector<std::weak_ptr<BaseComponent>> m_Components;
        bool m_MarkedForDelete;

	};
}
