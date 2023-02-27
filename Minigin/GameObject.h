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


        template<typename T>
        std::shared_ptr<T> AddComponent(std::shared_ptr<T> component) {
            
            m_Components.push_back(component);
            return component;
        }

        template<typename T>
        void removeComponent() {
            auto it = std::find_if(m_Components.begin(), m_Components.end(), [](const std::shared_ptr<BaseComponent>& c) {
                return dynamic_cast<T*>(c.get()) != nullptr;
                });
            if (it != m_Components.end()) {
                m_Components.erase(it);
            }
        }

        template<typename T>
        std::shared_ptr<T> GetComponent() const {
            for (const auto& component : m_Components) {
                if (std::shared_ptr<T> pointerType = std::dynamic_pointer_cast<T>(component)) {
                    return pointerType;
                }
            }
            return nullptr;
        }

        template<typename T>


        bool hasComponent() const {
            return GetComponent<T>() != nullptr;
        }


		GameObject() = default;
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		std::vector<std::shared_ptr<BaseComponent>> m_Components;

	};
}
