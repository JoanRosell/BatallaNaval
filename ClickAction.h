#pragma once
#include "Utilities.h"
#include "Action.h"
#include "Player.h"

// Accion que realiza un Player, se generan a raiz de eventos
class ClickAction : public Action
{
public:
	// Funciones eliminadas
	ClickAction() = delete;
	ClickAction(Player* source, Player* target, const coord& coordClicked);
	~ClickAction();

	ActionOutcome execute();
	const coord& getParameter() const { return parameter; }

	Action* clone() { return new ClickAction(*this); }
private:
	Player* source;
	Player* target;
	coord parameter;
};

