#pragma once

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual void Execute();
		virtual void Undo();
		virtual void Redo();

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
