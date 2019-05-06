#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "joc.h"
#include "Typedefs.h"

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
	bool isDestroyed() const { return destroyed; }
	int getSize() const { return size; }
	bool deploy(coord firstCoord);
	const std::vector<std::pair<bool, coord>>& getCells() const { return myCells; }
	#ifndef __NOT_GRAPHICS
		void askOrientation();
	#endif

private:
	Ship_Orientation orientation;
	std::vector<std::pair<bool, coord>> myCells;
	bool deployed;
	bool destroyed;
	int size;
	int activeCells;
};

