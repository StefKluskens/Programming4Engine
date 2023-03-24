#include "Command.h"

Command::Command(GameObject* pActor)
	: m_pActor(pActor)
{
}

Command::~Command()
{
}

void MoveCommand::Execute()
{
	//Get transform from m_pActor
	//change position with speed and deltaTime

}
