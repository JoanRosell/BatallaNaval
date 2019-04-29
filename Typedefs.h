#pragma once
#include <utility>

// Tipos de eventos que podemos procesar
enum class Event_Type
{
	mouse_event,
	keyboard_event
};

// Identificadores para cada jugador, se usan para saber que acciones 
// ha realizado un jugador y en que turno se esta jugando
enum class Player_ID
{
	PLAYER_ZERO,
	PLAYER_ONE
};

typedef std::pair<int, int> coord
