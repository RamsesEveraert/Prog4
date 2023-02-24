#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>

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
		void SetPosition(float x, float y);


		template<typename T>
		T* AddComponent(const std::string& nameComponent, T* pComponent)
		{

			static_assert(std::is_base_of< BaseComponent, T>::value, "T isn't derived from BaseComponent class!")

			std::pair<std::string, T*> component(nameComponent, pComponent);
			m_ComponentPntrs.insert(component);

			std::cout << "Component: " << nameComponent << " created!\n"

			return pComponent;
		}
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::unordered_map<std::string, BaseComponent*> m_ComponentPntrs;

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};
}
