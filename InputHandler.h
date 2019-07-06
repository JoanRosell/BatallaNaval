#pragma once
#include "Player.h"
#include "ClickAction.h"
#include "KeyboardAction.h"
#include <queue>
#include <utility>


class InputHandler
{
public:
	InputHandler() : human(nullptr), machine(nullptr) {}
	~InputHandler() {}
	void init(Player* h, Player* m);
	bool captureEvent();
	Action* processLastEvent();
	
	bool isReady() const { return (human != nullptr && machine != nullptr); }

private:
	Player* human;
	Player* machine;
	std::vector<SDL_Event> eventRecord;

	coord coordFromPixel(int x, int y);
};

