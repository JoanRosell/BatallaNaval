#pragma once
#include <fstream>
#include "InputHandler.h"
#include "UserInterface.h"
#include "Utilities.h"
#include "HumanPlayer.h"
#include "MachinePlayer.h"
#include <vector>

class Partida
{
public:
	Partida();
	~Partida();
	Partida(const std::string& initFileHuman, const std::string& initFileArtificial);
	void catchEvents();
	void drawGraphics();
	void update();
	void dumpToFile(); // TO REFACTOR
	void playTurn();
	bool isReady() const { return ready; }
	bool isFinished() const { return gameEnded; }

private:
	Player* humanPlayer;
	Player* machinePlayer;
	UserInterface ui;

	int turn;
	bool ready;
	bool gameEnded;

	void logBoardToFile(const char* filename, const std::vector<VisualizationCell>& board);
};

