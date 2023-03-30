#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) 
	: m_name(name)
	, m_Debug {true}
{
	m_pDebugger = std::make_unique<Debugger>(*this);
}
Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	object->SetParent(nullptr, false);

	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::Update()
{
	auto newObjects = DeleteMarkedObjects(m_Objects);
	m_Objects = std::move(newObjects);
	
		for (auto& object : m_Objects)
		{
			if (object->IsMarkedForDelete())
			{
				continue;
			}

			object->Update();
		}

		DeleteMarkedObjects(m_Objects);
		if (m_Debug) m_pDebugger->HandleShortKeys();


}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::RenderImGui()
{
	if(m_Debug) m_pDebugger->Render();
	
	for (const auto& object : m_Objects)
	{
		object->RenderImGui();
	}
}

const std::string& dae::Scene::GetName() const
{
	return m_name;
}

std::vector<std::shared_ptr<GameObject>> dae::Scene::GetSceneObjects() const
{
	return m_Objects;
}


std::vector<std::shared_ptr<GameObject>> Scene::DeleteMarkedObjects(std::vector<std::shared_ptr<GameObject>> objects)
{
	// Partition the vector into two parts:
	// - Objects marked for deletion
	// - Objects not marked for deletion

	auto partitionIt = std::partition(objects.begin(), objects.end(), [](std::shared_ptr<GameObject> obj) {
		return !obj->IsMarkedForDelete();
		});

	// Create a new vector filled with the objects not marked for deletion
	std::vector<std::shared_ptr<GameObject>> newObjects(objects.begin(), partitionIt);

	return newObjects;
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}
