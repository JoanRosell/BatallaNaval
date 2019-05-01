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
	Ship() : deployed(false), sank(false), size(0), 
		activeCells(0), orientation(Ship_Orientation::UNDEFINED) 
	{}

	Ship(int size) : deployed(false), 
		sank(false), size(size), activeCells(size), orientation(Ship_Orientation::UNDEFINED) {}

	Ship(int x, int y, int size, Ship_Orientation o);
	~Ship();

	bool isDeployed() const { return deployed; }
	bool isSank() const { return sank; }
	int getSize() const { return size; }
	bool deploy(coord firstCoord);
	void askOrientation();

private:
	Ship_Orientation orientation;
	std::vector<coord> myCoords;
	bool deployed;
	bool sank;
	int size;
	int activeCells;
};

