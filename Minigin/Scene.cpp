#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}
Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void dae::Scene::DeleteMarkedObjects(std::vector<std::shared_ptr<GameObject>>& objects)
{
	// Partition the vector into two parts:
	// - Objects marked for deletion
	// - Objects not marked for deletion

	auto partitionIt = std::partition(objects.begin(), objects.end(), [](const std::shared_ptr<GameObject>& obj) {
		return !obj->IsMarkedForDelete();
		});

	// Erase the objects marked for deletion
	objects.erase(partitionIt, objects.end());

	// Replace the vector with a new vector filled with the objects not marked for deletion
	std::vector<std::shared_ptr<GameObject>> newObjects(objects.begin(), partitionIt);
	objects = std::move(newObjects);
}


void Scene::Update()
{

	//TODO delete marked objets gives error
	
		for (auto& object : m_Objects)
		{
			if (object->IsMarkedForDelete())
			{
				std::cout << "Object marked for deletion and skipped\n";
				continue;
			}

			object->Update();
		}

		//DeleteMarkedObjects(m_Objects);

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


