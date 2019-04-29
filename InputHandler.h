#pragma once
#include "Player.h"
#include "Typedefs.h"
#include <memory>
#include <utility>

// Scoped enum or 'class' enum
enum class Action_Types
{
	DEPLOY,
	ATTACK
};

class InputHandler
{
public:
	InputHandler() : myPlayer(nullptr), deploymentRequested(false),
		attackRequested(false), deploymentServed(false), attackServed(false)
	{}
	~InputHandler();
	void interpretEvents();
	bool hasRequest() const { return deploymentRequested || attackRequested; }
	
	Action_Types getCurrentRequest();
	coord getSelectedCell() const { return currentCell; }
	Ship* getShipToDeploy() const { return &(*myPlayer->getCurrentShipToDeploy()); }
	void attach(Player* p) { myPlayer.reset(p); }
	void detach() { myPlayer = nullptr; }

private:
	std::unique_ptr<Player> myPlayer;
	coord mapGridCoord(int X, int Y);
	coord currentCell;
	bool deploymentRequested;
	bool deploymentServed;
	bool attackRequested;
	bool attackServed;
};

