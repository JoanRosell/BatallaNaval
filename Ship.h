#pragma once
#include "joc.h"
#include <memory>
#include <string>

class Ship
{
public:
	Ship() : img(nullptr), deployed(false), sank(false), size(0), activeCells(0) {}

	Ship(const char* path, int size) : img(new Sprite(path)), deployed(false), 
		sank(false), size(size), activeCells(size) {}
	~Ship();

	bool isDeployed() const { return deployed; }
	bool isSank() const { return sank; }
	void deployAt(int x, int y);
	void draw() const;
	
private:
	Sprite* img;
	int grid_X;
	int grid_Y;
	bool deployed;
	bool sank;
	int size;
	int activeCells;
};

