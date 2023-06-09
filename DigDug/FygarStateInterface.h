#pragma once
#include <memory>

namespace dae
{
	class FygarStateInterface
	{
	public:
		virtual ~FygarStateInterface() = default;

		virtual void OnEnter() = 0;
		virtual void OnEnd() = 0;

		virtual std::unique_ptr<FygarStateInterface> Update() = 0;
	};
}
