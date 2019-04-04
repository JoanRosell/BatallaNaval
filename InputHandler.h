#pragma once
#include "Player.h"
#include "joc.h"
#include <memory>
#include <utility>

class InputHandler
{
public:
	InputHandler() : myPlayer(nullptr) {}
	~InputHandler();
	void interpretEvents();
	void attach(Player* p) { myPlayer.reset(p); }
	void detach() { myPlayer = nullptr; }
private:
	std::shared_ptr<Player> myPlayer;
	std::pair<int, int> mapGridCoord(int X, int Y);
};

