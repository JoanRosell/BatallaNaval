#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Typedefs.h"
#include "Ship.h"

/*
	Define los posibles sprites que pueden 
	visualizarse en una posicion concreta
*/
enum class Sprite_Type
{
	NO_SPRITE,
	WATER,
	SHIP,
	DAMAGED_SHIP,
	DESTROYED_SHIP
};

class UserInterface
{
public:
	UserInterface()
	{
		deployBoard.resize(100, Sprite_Type::NO_SPRITE);
		attackBoard.resize(100, Sprite_Type::NO_SPRITE);
	}
	~UserInterface();
	void print() {}
	void init(const std::vector<Ship>& userShips, const std::vector<Ship>& machineShips);

	const std::vector<Sprite_Type>& getHumanBoard() const{ return deployBoard; }
	const std::vector<Sprite_Type>& getMachineBoard() const{ return attackBoard; }
		
private:
	//	Vectores 10x10 unidimensionales
	//	deployBoard contiene los barcos del usuario, siempre son visibles
	std::vector<Sprite_Type> deployBoard;
	//	attackBoard contiene los barcos del oponente, solo son visibles si han recibido un ataque
	std::vector<Sprite_Type> attackBoard;
	static const int rowSize = 10;
	//	Con esta sencilla funcion mapeamos una coordenada (x, y) a un indice [0, 99]
	int coordToIndex(coord thisCoord) { return (thisCoord.first*rowSize) + thisCoord.second; }
	
};

