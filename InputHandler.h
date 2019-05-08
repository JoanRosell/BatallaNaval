#pragma once
#include "Player.h"
#include "Typedefs.h"
#include <memory>
#include <utility>

// Scoped enum or 'class' enum
enum class Action_Type
{
	DEPLOY,
	ATTACK
};

class InputHandler
{
public:
	InputHandler() {}
	~InputHandler() {}
	void attach(Player* p) { myPlayer.reset(p); }
	void detach() { myPlayer = nullptr; }
	void waitForEvents();

private:
	std::unique_ptr<Player> myPlayer;
	coord coordFromPixel(int x, int y);
};

