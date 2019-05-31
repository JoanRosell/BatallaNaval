#pragma once
#include "joc.h"
#include "Player.h"
#include "Typedefs.h"
#include "Action.h"

// Accion que realiza un Player, se generan a raiz de eventos
class ClickAction : public Action
{
public:
	// Funciones eliminadas
	ClickAction() = delete;
	ClickAction(const ClickAction&) = delete;
	ClickAction(const ClickAction&&) = delete;
	ClickAction& operator=(const ClickAction&) = delete;

	ClickAction(Player* source, const coord& coordClicked);
	~ClickAction();

	Action_Outcome execute();

private:
	Player* source;
	coord parameter;
};

