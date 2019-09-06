#pragma once
#include "Action.h"
#include "joc.h"
#include "Utilities.h"

class Player;

class KeyboardAction :
	public Action
{
public:
	KeyboardAction() = delete;
	KeyboardAction(Player* s, SDL_Scancode kCode) : source(s), keyCode(kCode) {}
	~KeyboardAction();

	ActionOutcome execute() override;

	Action* clone() override { return new KeyboardAction(*this); }

private:
	Player* source;
	SDL_Scancode keyCode;
};

