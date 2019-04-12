#pragma once
#include "Ship.h"
#include "joc.h"
#include <vector>

class Player
{
public:
	Player();
	virtual ~Player();
	bool isDeploying() const { return true; }
	bool isAttacking() const { return true; }
	int getShipsAlive() const { return shipsAlive; }
	std::vector<Ship>::iterator getCurrentShipToDeploy() const { return currentShipToDeploy; }
	
protected:
	
private:
	unsigned int shipsAlive;
	unsigned int deployedShips;
	bool deploying;
	bool attacking;
	std::vector<Ship> fleet;
	std::vector<Ship>::iterator currentShipToDeploy;
	void buildFleet();
};



Player::Player() : deploying(true), attacking(false), deployedShips(0), currentShipToDeploy(fleet.begin())
{
	buildFleet();
	shipsAlive = fleet.size();
}




inline void Player::buildFleet()
{
	/*
	*	Hacer reserve --> emplace es mas eficiente
	*	por que no hacemos copias intermedias del objeto.
	*/

	int nTypes(kShipTypes);
	int currentShipSize(kMaxShipSize);
	int currentShipsToBuild(kMinShipQuantity);

	fleet.reserve(kMaxShipsPerPlayer);

	for (int type = 0; type < nTypes; type++)
	{
		for (int i = 0; i < currentShipsToBuild; i++)
			fleet.emplace_back("", currentShipSize); 
		
		currentShipSize--;
		currentShipsToBuild++;
	}
}

Player::~Player()
{
}