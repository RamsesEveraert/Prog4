#pragma once

#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual void Execute();
		virtual void Undo();
		virtual void Redo();

		virtual void SetDirection(const glm::vec2& direction) = 0;

		Command(GameObject* gameObject);
		virtual ~Command() = default;

		Command(const Command&) = default;
		Command(Command&&) = default;
		Command& operator=(const Command&) = default;
		Command& operator=(Command&&) = default;

	protected:
		GameObject* GetGameObject() const;

	private:
		GameObject* m_pGameObject;
	};
}
