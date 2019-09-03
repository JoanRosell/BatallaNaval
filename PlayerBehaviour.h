#pragma once
#include "Player.h"
#include "Utilities.h"

class PlayerBehaviour
{
public:
	PlayerBehaviour();
	virtual ~PlayerBehaviour();
	virtual ActionOutcome execute(Player* target) = 0;
};

