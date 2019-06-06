#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Utilities.h"


class Player
{
public:
	Player();
	~Player() {}
	
	bool isActive() const { return attacking; }
	int getShipsAlive() const { return shipsAlive; }
	
	//	Construye una flota a partir de un archivo txt
	bool loadShipsFromFile(const std::string& file);

	bool canAttackAt(const coord& c) const;
	void updateAtkCoords(const coord& c) { atkCoords.find(c)->second = true; }

	
	Outcome_Type processHit(const coord& c)
	{
		Outcome_Type oType(Outcome_Type::WATER);

		if (fleetIsHit(c))
		{
			lastShipHit->registerHit(c);
			if (lastShipHit->isDestroyed())
				oType = Outcome_Type::SHIP_DESTROYED;
			else
				oType = Outcome_Type::SHIP_HIT;
		}

		return oType;
	}

	Ship getLastShipHit() { return *lastShipHit; }

	void endActionPhase() { attacking = false; }
	void startActionPhase() { attacking = true; }
private:
	unsigned int shipsAlive;
	unsigned int deployedShips;
	bool attacking;
	std::vector<Ship> fleet;
	std::vector<Ship>::iterator lastShipHit;
	std::map<coord, bool> atkCoords;
	Player_Type type;
	void buildFleet();
	void buildAttackCoords(int startX, int startY);
	bool fleetIsHit(const coord& c) const;

	// Tipos de barcos diferentes
	static const int kShipTypes = 4;

	// Tamaño maximo de un barco
	static const int kMaxShipSize = 4;

	// Cantidad minima de barcos de cada tipo
	static const int kMinShipQuantity = 1;

	// Numero maximo de barcos por jugador
	static const int kMaxShipsPerPlayer = 10;

	static const short k_nCoords = 100;
};


inline Player::Player() : attacking(true), deployedShips(0)
{
	switch (type)
	{
	case Player_Type::MACHINE:
		buildAttackCoords(0, 10);
		break;
	
	case Player_Type::HUMAN:
		buildAttackCoords(0, 0);
		break;
	default:
		break;
	}
}

inline bool Player::loadShipsFromFile(const std::string & filename)
{
	bool shipsLoaded(false);
	std::string line;
	std::ifstream file;

	/*	Lectura de fichero:
	*		Para leer un fichero extraemos una linea entera
	*		y la transformamos en un input-stringstream para poder tratarla
	*		como un iostream (cout, cin, cerr, etc...) generico
	*/

	file.open(filename);

	/*	
		getline(istream&, string&) retorna istream&, pero cuando 
		usamos esta funcion en un ambito logico automaticamente testea los flags
		del istream, devolviendo un valor valido si el stream esta listo para operaciones de lectura
	*/
	while (std::getline(file, line))
	{
		std::istringstream shipData(line);
		int x;
		shipData >> x;
		int y;
		shipData >> y;
		int size;
		shipData >> size;
		/*	
			Podriamos extraer la orientacion como un bool, 
			pero seria mas complicado transformarlo a una orientacion valida
		*/
		int orientation;
		shipData >> orientation;
		//	Como orientation es un int debemos hacer un cast a Ship_Orientation para poder construir el barco
		//	Las coordenadas son un rango [1, 10], necesitamos transformar este rango a [0, 9]
		fleet.emplace_back(--x, --y, size, (Ship_Orientation)orientation);
	}
	file.close();

	deployedShips = fleet.size();

	if (deployedShips == 10)
	{
		shipsLoaded = true;
		attacking = true;
	}
	
	return shipsLoaded;
}


inline bool Player::canAttackAt(const coord & c) const
{
	bool atkCanBeMade(false);
	auto coordToAttack(atkCoords.find(c));
	
	if (coordToAttack != atkCoords.end())
		atkCanBeMade = !coordToAttack->second;
	
	return atkCanBeMade;
}

inline bool Player::fleetIsHit(const coord & c) const
{
	bool shipHit(false);

	for (const auto& ship : fleet)
	{
		shipHit = ship.isHit(c);
		
		if (shipHit)
		{
			*lastShipHit = ship;
			break;
		}	
	}

	return shipHit;
}

// Construye una flota de barcos sin desplegar
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

	/*	Algoritmo para generar los barcos:
	*	Para cada tipo de barco creamos tantos barcos
	*	como sea necesario
	*/
	for (int type = 0; type < nTypes; type++)
	{
		for (int i = 0; i < currentShipsToBuild; i++)
			fleet.emplace_back(currentShipSize); 
		
		currentShipSize--;
		currentShipsToBuild++;
	}
}

inline void Player::buildAttackCoords(int startX, int startY)
{
	for (int i = 0; i < k_nCoords; i++)
	{
		coord c{ startX, startY };
		atkCoords.emplace(std::make_pair(c, false));

		startX++;

		if (startX > 9)
		{
			startY++;
			startX = 0;
		}
	}
}
