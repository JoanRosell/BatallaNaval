#pragma once
#include "Player.h"
#include "Typedefs.h"
#include "ClickAction.h"
#include <memory>
#include <utility>


class InputHandler
{
public:
	InputHandler() {}
	~InputHandler() {}
	void attach(Player* p) { myPlayer = p; }
	void detach() { myPlayer = nullptr; }
	void waitForEvents();

private:
	Player* myPlayer;
	std::vector<Action*> actions;
	coord coordFromPixel(int x, int y);
};

