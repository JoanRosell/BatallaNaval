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

	ClickAction(Player* source, Player* target, const coord& coordClicked);
	~ClickAction();

	ActionOutcome execute();
	const coord& getParameter() const { return parameter; }

private:
	Player* source;
	Player* target;
	coord parameter;

	bool coordIsValid(const std::vector<attackCoord>::const_iterator & it, const std::vector<attackCoord>::const_iterator & end) const;
};

