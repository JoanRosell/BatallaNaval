#pragma once
#include <fstream>
#include <vector>
#include "UserInterface.h"
#include "HumanPlayer.h"
#include "MachinePlayer.h"


class Partida
{
public:
	Partida() = delete;
	Partida(const std::string& initFileHuman, const std::string& initFileArtificial);

	~Partida() // Como es el objeto mas longevo este es el encargado de liberar recursos
	{
		delete humanPlayer;
		humanPlayer = nullptr;

		delete machinePlayer;
		machinePlayer = nullptr;
	}

	void catchEvents() { ui.catchEvents(); }
	void drawGraphics() { ui.printGraphics(); }
	void update() { ui.update(); }
	void run(); 

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
	ActionOutcome playTurn();
	void passTurn();
	void updateTurnState(ActionOutcome& outcome);
};

