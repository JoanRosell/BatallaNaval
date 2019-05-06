#pragma once
#include <string>
#include <vector>
#include "Typedefs.h"
#include "Ship.h"

/*
	Define los posibles sprites que pueden 
	visualizarse en una coordenada concreta
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
		humanBoard.resize(nRows*nCols, Sprite_Type::NO_SPRITE);
		machineBoard.resize(nRows*nCols, Sprite_Type::NO_SPRITE);
	}
	~UserInterface();
	bool init(const std::vector<Ship>& userShips, const std::vector<Ship>& machineShips);

	const std::vector<Sprite_Type>& getHumanBoard() const { return humanBoard; }
	const std::vector<Sprite_Type>& getMachineBoard() const { return machineBoard; }
		
private:
	//	Vectores 10x10 unidimensionales
	//	humanBoard contiene los barcos del usuario, siempre son visibles
	std::vector<Sprite_Type> humanBoard;
	//	machineBoard contiene los barcos del oponente, solo son visibles si han recibido un ataque
	std::vector<Sprite_Type> machineBoard;
	static const int nRows = 10;
	static const int nCols = 10;
	//	Con esta sencilla funcion mapeamos una coordenada (x, y) a un indice [0, 99]
	int coordToIndex(coord thisCoord) { return (thisCoord.first*nRows) + thisCoord.second; }
	bool loadBoard(std::vector<Sprite_Type>& board, const std::vector<Ship>& ships);
	void updateBoard(std::vector<Sprite_Type>& board, const std::pair<bool, coord>& cell, bool shipIsDestroyed);
	Sprite_Type updateSpriteType(const Sprite_Type& oldType, bool positionAttacked, bool shipIsDestroyed);
	
};

