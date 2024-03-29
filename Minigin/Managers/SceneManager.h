#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:

		std::vector<std::shared_ptr<Scene>> GetScenes() const;

		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate(/* float fixedTimeStep */);
		void Render();
		void RenderImGui();

		void RemoveScene(Scene* scene);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
