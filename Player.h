#pragma once
#include "Ship.h"
#include <fstream>
#include <sstream>
#include <vector>

class Player
{
public:
	Player();
	~Player() {}
	bool isDeploying() const { return true; }
	bool isAttacking() const { return true; }
	int getShipsAlive() const { return shipsAlive; }
	std::vector<Ship>::iterator getCurrentShipToDeploy() const { return currentShipToDeploy; }
	bool loadShipsFromFile(const std::string& file);
private:
	unsigned int shipsAlive;
	unsigned int deployedShips;
	bool deploying;
	bool attacking;
	std::vector<Ship> fleet;
	std::vector<Ship>::iterator currentShipToDeploy;
	void buildFleet();

	// Tipos de barcos diferentes
	const int kShipTypes = 4;

	// Tamaño maximo de un barco
	const int kMaxShipSize = 4;

	// Cantidad minima de barcos de cada tipo
	const int kMinShipQuantity = 1;

	// Numero maximo de barcos por jugador
	const int kMaxShipsPerPlayer = 10;
};



inline Player::Player() : deploying(true), attacking(false), deployedShips(0)
{
}

inline bool Player::loadShipsFromFile(const std::string & filename)
{
	bool shipsLoaded(false);
	std::string line;
	std::ifstream file;

	file.open(filename);
	while (std::getline(file, line))
	{
		std::istringstream shipData(line);
		int x;
		shipData >> x;
		int y;
		shipData >> y;
		int size;
		shipData >> size;
		int orientation;
		shipData >> orientation;
		fleet.emplace_back(x, y, size, (Ship_Orientation)orientation);
	}

	if (fleet.size() == 10)
		shipsLoaded = true;
	
	return shipsLoaded;
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
			fleet.emplace_back(currentShipSize); 
		
		currentShipSize--;
		currentShipsToBuild++;
	}
}