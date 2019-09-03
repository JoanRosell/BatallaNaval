#pragma once
#include "PlayerBehaviour.h"
#include "InputHandler.h"

class HumanBehaviour :
	public PlayerBehaviour
{
public:
	HumanBehaviour() = delete;
	HumanBehaviour(Player* p) : PlayerBehaviour(), ih(p) {}
	~HumanBehaviour();
	ActionOutcome execute(Player* target);

private:
	InputHandler ih;
};

