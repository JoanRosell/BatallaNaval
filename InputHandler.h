#pragma once
#include "Player.h"
#include "Typedefs.h"
#include "ClickAction.h"
#include <queue>
#include <utility>


class InputHandler
{
public:
	InputHandler() : human(nullptr), machine(nullptr) {}
	~InputHandler() {}
	void init(Player* h, Player* m);
	bool waitForEvents();
	Action* retrieveLastAction();

private:
	Player* human;
	Player* machine;
	std::queue<Action*> actions;
	coord coordFromPixel(int x, int y);
};

