#include "SceneManager.h"
#include "Scene.h"




using namespace dae;

void SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

//todo for physics later (?)

void SceneManager::FixedUpdate()
{
	/*m_FixedTimeStep = fixedTimeStep;*/

	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}


void SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderImGui()
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderImGui();
	}
}

void dae::SceneManager::RemoveScene(Scene* scene)
{
	m_scenes.erase(std::remove_if(m_scenes.begin(), m_scenes.end(), [&](std::shared_ptr<Scene> pScene) { return scene == pScene.get(); }));
}

std::vector<std::shared_ptr<Scene>> dae::SceneManager::GetScenes() const
{
	return m_scenes;
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
