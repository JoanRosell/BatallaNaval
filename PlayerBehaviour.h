#pragma once
#include "Utilities.h"
#include "Player.h"

class PlayerBehaviour
{
public:
	PlayerBehaviour() {}
	virtual ~PlayerBehaviour() {}
	virtual ActionOutcome execute(Player* target) = 0;
};

