#pragma once
#include "Player.h"
#include "ClickAction.h"
#include <queue>
#include <utility>


class InputHandler
{
public:
	InputHandler() : human(nullptr), machine(nullptr), ready(false) {}
	~InputHandler() {}
	void init(Player* h, Player* m);
	bool waitForEvents();
	Action* retrieveLastAction();
	void updateActionQueue();
	bool isReady() const { return ready; }
private:
	Player* human;
	Player* machine;
	std::queue<Action*> actions;
	bool ready;
	coord coordFromPixel(int x, int y);
};

