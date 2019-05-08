#pragma once
#include "joc.h"
#include "InputHandler.h"

// Accion que realiza un player, se generan a raiz de eventos
class Action
{
public:
	// Funciones eliminadas
	Action() = delete;
	Action(const Action&) = delete;
	Action(const Action&&) = delete;
	Action& operator=(const Action&) = delete;

	Action(const SDL_Event& e);
	~Action();
private:
	Action_Type type;
};

