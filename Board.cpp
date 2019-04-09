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
		deployShipAt(playerListener->getSelectedCell()); // TO DO
		break;
	case Request_Types::ATTACK:
		//	Attack enemy board
		break;
	default:
	}
	return requestAttended;
}

bool Board::deployShipAt(Coord thisCoord)
{
	bool shipDeployed(false);
	Ship* shipToDeploy = playerListener->getShipToDeploy();

	if (shipToDeploy->getShipOrientation() == Ship_Orientation::UNDEFINED)
		shipToDeploy->setOrientation(askOrientation());

	shipDeployed = assignCoordinates(thisCoord, shipToDeploy);
	// SET CELL REFERENCES TO POINT TO THE SHIP
	// NOTIFY playerListener
	return false;
}

bool Board::assignCoordinates(Coord firstCoord, Ship* shipToDeploy)
{
	bool shipAssigned(false);
	int shipSize = shipToDeploy->getSize();
	Ship_Orientation currentOrientation(shipToDeploy->getShipOrientation());

	switch (currentOrientation)
	{
	case Ship_Orientation::TOP:
		if (true) //	Check if the ship fits 
			//	Function call to assign ship
		break;
	case Ship_Orientation::RIGHT:
		break;
	case Ship_Orientation::BOTTOM:
		break;
	case Ship_Orientation::LEFT:
		break;
	case Ship_Orientation::UNDEFINED:
		break;
	default:
		break;
	}
	return false;
}

Ship_Orientation Board::askOrientation()
{
	return Ship_Orientation();
}
