#pragma once
#include "Player.h"
#include "joc.h"
#include <memory>
#include <utility>
typedef std::pair<int, int> Coord;

// Scoped enum or 'class' enum
enum class Request_Types
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
	
	Request_Types getCurrentRequest();
	Coord getSelectedCell() const { return currentCell; }
	Ship* getShipToDeploy() const { return &(*myPlayer->getCurrentShipToDeploy()); }
	void attach(Player* p) { myPlayer.reset(p); }
	void detach() { myPlayer = nullptr; }

private:
	std::shared_ptr<Player> myPlayer;
	Coord mapGridCoord(int X, int Y);
	Coord currentCell;
	bool deploymentRequested;
	bool deploymentServed;
	bool attackRequested;
	bool attackServed;
};

