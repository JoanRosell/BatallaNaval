#pragma once
#include "Action.h"
#include "Player.h"

class KeyboardAction :
	public Action
{
public:
	KeyboardAction() = delete;
	KeyboardAction(Player* pPlayer, SDL_Scancode kCode) : source(pPlayer), keyCode(kCode) {}
	~KeyboardAction();

	ActionOutcome execute();

	Action* clone() { return new KeyboardAction(*this); }
private:
	Player* source;
	SDL_Scancode keyCode;
};

