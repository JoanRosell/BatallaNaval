#include "InputHandler.h"

InputHandler::~InputHandler()
{
}

void InputHandler::interpretEvents()
{
	if (myPlayer == nullptr)
		return;

	if (Mouse_getButLeft())
	{
		currentCell = mapGridCoord(Mouse_getX(), Mouse_getY());

		if (myPlayer->isDeploying())
			deploymentRequested = true;

		if (myPlayer->isAttacking())
			attackRequested = true;
	}
}

Request_Types InputHandler::getCurrentRequest()
{
	if (deploymentRequested)
		return Request_Types::DEPLOY;

	if (attackRequested)
		return Request_Types::ATTACK;
}

std::pair<int, int> InputHandler::mapGridCoord(int X, int Y)
{
	return std::pair<int, int>(((int)Mouse_getX() / MIDA_CASELLA) * MIDA_CASELLA, ((int)Mouse_getY() / MIDA_CASELLA) * MIDA_CASELLA);
}
