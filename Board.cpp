#include "Board.h"

Board::~Board()
{
}

bool Board::processEvents()
{
	bool eventPending(false);

	if (playerListener->hasRequest())
	{
		eventPending = true;

		Action_Types currentRequest = playerListener->getCurrentRequest();

		if (attendRequest(currentRequest))
			eventPending = false;
	}

	return !eventPending;
}

bool Board::attendRequest(Action_Types request)
{
	bool requestAttended(false);

	switch (request)
	{
	case Action_Types::DEPLOY:
		playerListener->getShipToDeploy()->deploy(playerListener->getSelectedCell());
		shipsDeployed.push_back(playerListener->getShipToDeploy());
		break;
	case Action_Types::ATTACK:
		//	Attack enemy board
		break;
	default: break;
	}
	return requestAttended;
}
