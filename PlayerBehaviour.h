#pragma once

class Player;
struct ActionOutcome;

class PlayerBehaviour
{
public:
	PlayerBehaviour() {}
	virtual ~PlayerBehaviour() {}
	virtual ActionOutcome execute(Player* target) = 0;
};

