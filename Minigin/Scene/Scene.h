#pragma once
#include "SceneManager.h"
#include "Debugger.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;
		void RenderImGui();

		const std::string& GetName() const;
		std::vector< std::shared_ptr<GameObject>> GetSceneObjects() const;

		std::shared_ptr<GameObject>  FindObject(const std::string& name) const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::vector<std::shared_ptr<GameObject>> DeleteMarkedObjects(std::vector<std::shared_ptr<GameObject>> objects);
		

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_DeletedObjects{};

		// debugger
		//std::unique_ptr<Debugger> m_pDebugger;
		bool m_Debug;

		static unsigned int m_idCounter; 
	};

}
