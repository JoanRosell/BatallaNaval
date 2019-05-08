#pragma once
#include "Player.h"
#include <fstream>
#include "InputHandler.h"
#include "UserInterface.h"
#include "Typedefs.h"
#include <vector>
class Partida
{
public:
	Partida();
	~Partida();
	bool init(const std::string& initFileHuman, const std::string& initFileArtificial);
	bool processEvents();
	void dumpToFile();
private:
	Player humanPlayer;
	Player artificialPlayer;
	InputHandler playerListener;
	UserInterface ui;
	int turn;

	void logBoardToFile(const char* filename, const std::vector<Sprite_Type>& board);
};

