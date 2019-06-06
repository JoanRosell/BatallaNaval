#pragma once
#include "Player.h"
#include <fstream>
#include "InputHandler.h"
#include "UserInterface.h"
#include "Utilities.h"
#include <vector>

class Partida
{
public:
	Partida();
	~Partida();
	bool init(const std::string& initFileHuman, const std::string& initFileArtificial);
	void processEvents();
	void drawGraphics();
	void update();
	void dumpToFile(); // TO REFACTOR
	void playTurn();

private:
	Player humanPlayer;
	Player machinePlayer;
	InputHandler playerListener;
	UserInterface ui;
	int turn;

	void logBoardToFile(const char* filename, const std::vector<VisualizationCell>& board);
};

