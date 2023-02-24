#pragma once

namespace dae
{

	class BaseComponent
	{

	public:

		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		// Disabling copy/move constructors and assignment operators   
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	};

}


