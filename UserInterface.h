#pragma once
#include <string>
#include <vector>
#include "Ship.h"
#include <algorithm>
#include "Action.h"

/*
	Define los posibles sprites que pueden 
	visualizarse en una coordenada concreta
*/

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
	void updateChanges(const ActionOutcome& outcome);
	
	void printGraphics();
	const std::vector<VisualizationCell>& getVBoard() const { return vBoard; }
		
private:
	std::vector<VisualizationCell> vBoard;
	static const int nRows = 10;
	static const int nCols = 10;

	Screen screen;
	Sprite boardImg;
	Sprite shipImg;
	
	void registerPlayerShips(const std::vector<Ship>& ships, bool isHidden = false);
	void updateCell(coord coord, Sprite_Type newType, bool isHidden);
	void updateShipDestroyed(const Ship& s);
	void printBoard(std::vector<Sprite_Type>& boardToPrint, int startPos, bool visibility);
};

