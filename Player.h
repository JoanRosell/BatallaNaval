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
	bool isDeploying() const { return deploying; }
	bool isAttacking() const { return attacking; }
	int getShipsAlive() const { return shipsAlive; }
	
	//	Construye una flota a partir de un archivo txt
	bool loadShipsFromFile(const std::string& file);
	const std::vector<Ship>& getShips() const { return fleet; }
	
private:
	unsigned int shipsAlive;
	unsigned int deployedShips;
	bool deploying;
	bool attacking;
	std::vector<Ship> fleet;
	
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
		deploying = false;
		attacking = true;
	}
	
	return shipsLoaded;
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