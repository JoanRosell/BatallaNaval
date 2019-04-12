#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "joc.h"

class Ship
{
public:
	Ship() : img(nullptr), deployed(false), sank(false), size(0), 
		activeCells(0), orientation(Ship_Orientation::UNDEFINED) 
	{}

	Ship(const char* path, int size) : img(new Sprite(path)), deployed(false), 
		sank(false), size(size), activeCells(size) {}
	~Ship();

	bool isDeployed() const { return deployed; }
	bool isSank() const { return sank; }
	int getSize() const { return size; }
	void draw() const;
	bool deploy(Coord firstCoord);
	
	

private:
	Sprite* img;
	Ship_Orientation orientation;
	std::vector<Cell> myCoords;
	bool deployed;
	bool sank;
	int size;
	int activeCells;

	void askOrientation();
};

