#pragma once

#include "BaseComponent.h"

#include <memory>
#include <string>


namespace dae
{
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(const std::weak_ptr<GameObject>& gameObject);


		void Update(/*float deltaTime*/) override;
		void Render() const override;

		// Disabling copy/move constructors and assignment operators   
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

	private:
	};
}