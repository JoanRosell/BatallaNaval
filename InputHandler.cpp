#include "InputHandler.h"

void InputHandler::waitForEvents()
{
	SDL_Event input;
	// El segundo parametro son los milisegundos que se espera antes de continuar con la ejecución del proceso
	if (SDL_WaitEventTimeout(&input, 100))
		if (input.type == SDL_MOUSEBUTTONDOWN)
		{
			coord positionClicked(coordFromPixel(input.button.x, input.button.y));
		}
}

coord InputHandler::coordFromPixel(int x, int y)
{
	int coord_X = (x / MIDA_CASELLA) * MIDA_CASELLA;
	int coord_Y = (y / MIDA_CASELLA) * MIDA_CASELLA;

	return coord(coord_X, coord_Y);
}
