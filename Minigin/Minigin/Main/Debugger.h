#pragma once
#include "imgui.h"
#include "Scene.h"
#include <vector>
#include <memory>

namespace dae
{
	class Scene;
	class Debugger final
	{
	public:

		void Render();

		Debugger();
		~Debugger() = default;

		Debugger(const Debugger& other) = delete;
		Debugger(Debugger&& other) noexcept = delete;
		Debugger& operator=(const Debugger& other) = delete;
		Debugger& operator=(Debugger&& other) noexcept = delete;

	private:

		// ****** Scene info ******** //

		std::vector<std::shared_ptr<Scene>> m_Scenes;

		// ****** global info ******** //

		// Dear ImGui input/output struct
		/*ImGuiIO& m_Io;*/

		void ShowSceneInformation();
		void ShowGlobalInformation();

	};

}

