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
	InputHandler() {}
	~InputHandler() {}
	void attach(Player* p) { myPlayer.reset(p); }
	void detach() { myPlayer = nullptr; }

private:
	std::unique_ptr<Player> myPlayer;
};

