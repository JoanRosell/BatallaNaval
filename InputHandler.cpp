#include "InputHandler.h"

InputHandler::~InputHandler()
{
}

void InputHandler::interpretEvents()
{
	if (myPlayer == nullptr)
		return;

	int x = 0;
	int y = 0;
	std::pair<int, int> gridCoord(x, y);

	if (Mouse_getButLeft())
	{
		gridCoord = mapGridCoord(Mouse_getX(), Mouse_getY());
	}
		
}

std::pair<int, int> InputHandler::mapGridCoord(int X, int Y)
{
	return std::pair<int, int>(((int)Mouse_getX() / MIDA_CASELLA) * MIDA_CASELLA, ((int)Mouse_getY() / MIDA_CASELLA) * MIDA_CASELLA);
}
