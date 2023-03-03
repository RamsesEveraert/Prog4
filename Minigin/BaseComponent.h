#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{

	public:


		virtual void Update();
		virtual void Render() const;

		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	
	protected:

		explicit BaseComponent(std::weak_ptr<GameObject> owner);

		std::shared_ptr<GameObject> GetOwner() const;


	private:

		std::weak_ptr<GameObject> m_pOwner;		

	};

}


