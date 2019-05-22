#pragma once
#include "joc.h"
#include "InputHandler.h"
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

	ClickAction(Player* target, const coord& coordClicked);
	~ClickAction();

	void execute() { return; }

private:
	Player* target;
	coord parameter;
};

