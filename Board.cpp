#include "Board.h"



Board::Board()
{
}


Board::~Board()
{
}

bool Board::processEvents()
{
	bool eventPending(false);

	if (playerListener->hasRequest())
	{
		eventPending = true;

		Request_Types currentRequest = playerListener->getCurrentRequest();

		if (attendRequest(currentRequest))
			eventPending = false;
	}

	return !eventPending;
}

bool Board::attendRequest(Request_Types request)
{
	bool requestAttended(false);

	switch (request)
	{
	case Request_Types::DEPLOY:
		playerListener->getShipToDeploy()->deploy(playerListener->getSelectedCell());
		shipsDeployed.push_back(playerListener->getShipToDeploy());
		break;
	case Request_Types::ATTACK:
		//	Attack enemy board
		break;
	default:
	}
	return requestAttended;
}
