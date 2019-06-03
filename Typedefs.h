#pragma once
#include <utility>

enum class Ship_Orientation
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
	UNDEFINED
};

struct coord
{
	unsigned short _x;
	unsigned short _y;

	bool operator==(const coord& rhs) const
	{
		return _x == rhs._x && _y == rhs._y;
	}
};