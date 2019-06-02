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
	UserInterface() : screen(MIDA_X, MIDA_Y * 2), boardImg("Program\\data\\caselles.png"), shipImg("Program\\data\\vaixell.png")
	{
		// Dejamos la pantalla preparada, el metodo show solo debe hacerse una vez
		screen.show();
		humanBoard.resize(nRows*nCols, Sprite_Type::NO_SPRITE);
		machineBoard.resize(nRows*nCols, Sprite_Type::NO_SPRITE);
	}
	~UserInterface();
	bool init(const std::vector<Ship>& userShips, const std::vector<Ship>& machineShips);
	// Screen tambien controla parte de la gestion de eventos...
	void catchEvents() { screen.processEvents(); }
	// Esto hay que extenderlo o sobrecargarlo para hacer actualizaciones de forma inteligente
	// Actualizar solamente los datos modificados en el ultimo turno
	void update() { screen.update(); }
	void updateCell(coord pos, Sprite_Type newType, bool isHumanBoard);
	void updateShipStatus(Ship* ship, bool isHumanBoard);
	void printGraphics();
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
	Screen screen;
	Sprite boardImg;
	Sprite shipImg;
	//	Con esta sencilla funcion mapeamos una coordenada (x, y) a un indice [0, 99]
	int coordToIndex(coord thisCoord) { return (thisCoord.first*nRows) + thisCoord.second; }
	bool loadBoard(std::vector<Sprite_Type>& board, const std::vector<Ship>& ships);
	void updateBoard(std::vector<Sprite_Type>& board, const Ship& ship);
	void updateSpriteType(Sprite_Type& oldType, bool positionAttacked, bool shipIsDestroyed);
	void printBoard(std::vector<Sprite_Type>& boardToPrint, int startPos, bool visibility);
	
};

