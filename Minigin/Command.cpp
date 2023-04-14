#include "Command.h"

using namespace dae;

void dae::Command::Execute()
{
}

void dae::Command::Undo()
{
}

void dae::Command::Redo()
{
}


Command::Command(GameObject* gameObject)
	: m_pGameObject{ gameObject }
{

}

dae::GameObject* dae::Command::GetGameObject() const
{
	return m_pGameObject;
}
