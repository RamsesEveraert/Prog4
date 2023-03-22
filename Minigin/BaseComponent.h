#pragma once
#include <memory>
#include <string>

namespace dae
{
	class GameObject;
	class BaseComponent
	{

	public:


		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void RenderImGui();

		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		std::shared_ptr<GameObject> GetOwner() const;
		const std::string GetIdentifier() const;
	
	protected:

		explicit BaseComponent(std::weak_ptr<GameObject> owner, const std::string& identifier = "");

		std::string m_Identifier;

		

	private:

		std::weak_ptr<GameObject> m_pOwner;		

	};

}


