#pragma once
#include <memory>
#include <string>

namespace dae
{
	class GameObject;
	class Component
	{

	public:


		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void RenderImGui();

		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		GameObject* GetOwner() const;
		void SetOwner(GameObject* owner);

	
	protected:

		Component();

		

	private:

		GameObject* m_pOwner;	

	};

}


