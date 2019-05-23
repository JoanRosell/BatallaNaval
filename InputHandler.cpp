#include "InputHandler.h"

void InputHandler::waitForEvents()
{
	SDL_Event input;
	if (SDL_WaitEvent(&input))
		if (input.type == SDL_MOUSEBUTTONDOWN)
		{
			coord positionClicked(coordFromPixel(input.button.x, input.button.y));
			actions.push_back(new ClickAction(myPlayer, positionClicked));
		}
}

coord InputHandler::coordFromPixel(int x, int y)
{
	int coord_X = (x / MIDA_CASELLA) * MIDA_CASELLA;
	int coord_Y = (y / MIDA_CASELLA) * MIDA_CASELLA;

	return coord(coord_X, coord_Y);
}
