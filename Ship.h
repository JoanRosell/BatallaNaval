#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "joc.h"

typedef std::pair<int, int> coord;

enum class Ship_Orientation
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
	UNDEFINED
};

class Ship
{
public:
	Ship() : deployed(false), size(0), 
		activeCells(0), orientation(Ship_Orientation::UNDEFINED) {}

	Ship(int size) : deployed(false), size(size), activeCells(size), orientation(Ship_Orientation::UNDEFINED) {}

	Ship(int x, int y, int size, Ship_Orientation o);
	~Ship();

	bool isDeployed() const { return deployed; }
	bool isDestroyed() const { return activeCells == 0; }
	int getSize() const { return size; }
	bool deploy(coord firstCoord);
	void registerHit(coord pos);
	bool isHit(const coord& c) const;

	const std::map<coord, bool>& getCells() const { return cells; }

	#ifndef __NOT_GRAPHICS
	void askOrientation();
	#endif

private:
	Ship_Orientation orientation;
	std::map<coord, bool> cells;

	bool deployed;
	int size;
	int activeCells;
};

