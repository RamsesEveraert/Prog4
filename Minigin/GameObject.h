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

	// todo: this should become final.
	class GameObject 
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		/*void SetPosition(const glm::vec3& position);*/


        template<typename T>
        void addComponent(std::shared_ptr<T> component) {
            m_Components.push_back(component);
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
        std::shared_ptr<T> getComponent() const {
            for (const auto& component : m_Components) {
                if (std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(component)) {
                    return t;
                }
            }
            return nullptr;
        }

        template<typename T>


        bool hasComponent() const {
            return getComponent<T>() != nullptr;
        }


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//TransformComponent m_transform{};
		std::vector<std::shared_ptr<BaseComponent>> m_Components;

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};
}
