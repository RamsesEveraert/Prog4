#pragma once

#include "BaseComponent.h"
#include "imgui.h"


namespace dae
{
	class DebugComponent final : public BaseComponent
	{
	public:

		DebugComponent();
		~DebugComponent() = default;

		virtual void Render();

	private:

		//global info
		float m_TimeRunning;
		ImGuiIO& m_Io;
		//object info
		std::string m_NameGameObject;


		void GameObjectInformation();
	};

}


