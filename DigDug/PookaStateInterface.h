#pragma once
#include <memory>

namespace dae
{
	class PookaStateInterface
	{
	public:
		virtual ~PookaStateInterface() = default;

		virtual void OnEnter() = 0;
		virtual void OnEnd() = 0;

		virtual std::unique_ptr<PookaStateInterface> Update() = 0;
	};
}


