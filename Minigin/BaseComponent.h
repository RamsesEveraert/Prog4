#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{

	public:

		BaseComponent(const std::weak_ptr<GameObject>& gameObject) : m_GameObject(gameObject) {}

		std::shared_ptr<GameObject> getGameObject() const {
			return m_GameObject.lock();
		}

		virtual void Update(/*float deltaTime*/) = 0 ;
		virtual void Render() const = 0;

		virtual ~BaseComponent() = default;

		// Disabling copy/move constructors and assignment operators   
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	
	protected:
		std::weak_ptr<GameObject> m_GameObject;
		

	};

}


