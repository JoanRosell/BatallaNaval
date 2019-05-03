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

enum class Cell_State
{
	ALIVE,
	DEAD
};

enum class Cell_Contents
{
	WATER,
	SHIP
};

enum class Ship_Orientation
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
	UNDEFINED
};

typedef std::pair<int, int> coord;

typedef std::pair<coord, Cell_Contents> cell;