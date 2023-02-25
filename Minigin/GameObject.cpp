
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <string>



dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	/*for (const auto& componentPtr : m_ComponentPointers)
	{
		if(componentPtr)
		componentPtr.get()->Update();
	}*/
}

void dae::GameObject::Render() const
{
	/*const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);*/
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

//void dae::GameObject::SetPosition(const glm::vec3& position)
//{
//	//m_transform.SetPosition(position);
//}
