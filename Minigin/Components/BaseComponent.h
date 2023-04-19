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

		GameObject* GetOwner() const;
		void SetOwner(GameObject* owner);
		const std::string GetIdentifier() const;

	
	protected:

		BaseComponent() = default;

		std::string m_Identifier;

		

	private:

		GameObject* m_pOwner;	

	};

}


