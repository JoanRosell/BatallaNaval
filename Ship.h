#pragma once
#include "joc.h"
#include <memory>
#include <string>

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
	Ship_Orientation getShipOrientation() const { return orientation; }
	void setOrientation(Ship_Orientation newOrientation) { orientation = newOrientation; }

private:
	Sprite* img;
	Ship_Orientation orientation;
	bool deployed;
	bool sank;
	int size;
	int activeCells;
};

