#include "InputHandler.h"

bool InputHandler::waitForEvents()
{
	bool eventCaptured(false);

	while (!eventCaptured)
	{
		SDL_Event input;
		if (SDL_WaitEvent(&input))
			if (input.type == SDL_MOUSEBUTTONDOWN)
			{
				coord positionClicked(coordFromPixel(input.button.x, input.button.y));
				actions.push_back(new ClickAction(myPlayer, positionClicked));
				eventCaptured = true;
			}
	}

	return eventCaptured;
}

Action_Outcome InputHandler::executeLastAction()
{
	Action* lastAction = actions.back();
	Action_Outcome result(Action_Outcome::UNDEFINED);

	if (!lastAction->isDone())
		result = lastAction->execute();
	
	return result;
}

coord InputHandler::coordFromPixel(int x, int y)
{
	int coord_X = (x / MIDA_CASELLA) * MIDA_CASELLA;
	int coord_Y = (y / MIDA_CASELLA) * MIDA_CASELLA;

	return coord(coord_X, coord_Y);
}
