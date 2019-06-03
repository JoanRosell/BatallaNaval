#pragma once
#include <string>
#include <vector>
#include "Typedefs.h"
#include "Ship.h"
#include <algorithm>

/*
	Define los posibles sprites que pueden 
	visualizarse en una coordenada concreta
*/
enum class Sprite_Type
{
	WATER,
	SHIP,
	DAMAGED_SHIP,
	DESTROYED_SHIP
};

typedef struct VisualizationCell
{
	coord coord;
	Sprite_Type spriteType;
	bool isHidden;
};

class UserInterface
{
public:
	UserInterface() : screen(MIDA_X, MIDA_Y * 2), boardImg("Program\\data\\caselles.png"), shipImg("Program\\data\\vaixell.png")
	{
		// Dejamos la pantalla preparada, el metodo show solo debe hacerse una vez
		screen.show();
	}
	~UserInterface();
	bool init(const std::vector<Ship>& userShips, const std::vector<Ship>& machineShips);
	// Screen tambien controla parte de la gestion de eventos...
	void catchEvents() { screen.processEvents(); }
	void update() { screen.update(); }
	void updateCell(VisualizationCell newCellState);
	void updateShipStatus(const Ship& ship, bool defaultVisibility);
	void printGraphics();
	const std::vector<VisualizationCell>& getVBoard() const { return vBoard; }
		
private:
	std::vector<VisualizationCell> vBoard;
	static const int nRows = 10;
	static const int nCols = 10;

	Screen screen;
	Sprite boardImg;
	Sprite shipImg;
	
	
	void printBoard(std::vector<Sprite_Type>& boardToPrint, int startPos, bool visibility);
	
};

