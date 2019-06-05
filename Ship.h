#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "joc.h"
#include "Typedefs.h"
#include <algorithm>
#include <map>

typedef struct cell
{
	coord coord;
	bool isHit;

	bool operator==(const cell& rhs)
	{
		return coord == rhs.coord && isHit == rhs.isHit;
	}
};

class Ship
{
public:
	Ship() : deployed(false), destroyed(false), size(0), 
		activeCells(0), orientation(Ship_Orientation::UNDEFINED) {}

	Ship(int size) : deployed(false), 
		destroyed(false), size(size), activeCells(size), orientation(Ship_Orientation::UNDEFINED) {}

	Ship(int x, int y, int size, Ship_Orientation o);
	~Ship();

	bool isDeployed() const { return deployed; }
	bool isDestroyed() const { return activeCells == 0; }
	int getSize() const { return size; }
	bool deploy(coord firstCoord);
	const std::vector<cell>& getCells() const { return myCells; }
	bool registerHit(coord pos);
	bool isHit(const coord& c) const;

	#ifndef __NOT_GRAPHICS
	void askOrientation();
	#endif

private:
	Ship_Orientation orientation;
	std::vector<cell> myCells;
	std::map<coord, bool> cells;
	bool deployed;
	bool destroyed;
	int size;
	int activeCells;
};

