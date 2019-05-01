#pragma once
#include "Player.h"
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
private:
	Player humanPlayer;
	Player artificialPlayer;
	InputHandler playerListener;
	UserInterface ui;
	int turn;
};

