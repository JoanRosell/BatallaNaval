#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include "Typedefs.h"
#include "Ship.h"

class UserInterface
{
public:
	UserInterface() {}
	~UserInterface();
	void print() {}
	void init() {}
	
private:
	std::vector<std::pair<coord, bool>> deployBoard;
	std::vector<std::pair<coord, bool>> attackBoard;
	std::vector<coord> sunkenShips;
};

