#include "InputHandler.h"

void InputHandler::init(Player * h, Player * m)
{
	if (human != nullptr || machine != nullptr)
		return;
	else
	{
		human = h;
		machine = m;
	}
}

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
				actions.push(new ClickAction(human, machine, positionClicked));
				eventCaptured = true;
			}
	}

	return eventCaptured;
}

Action * InputHandler::retrieveLastAction()
{
	if (!actions.empty())
		return actions.back();
	else
		return nullptr;
}

coord InputHandler::coordFromPixel(int x, int y)
{
	int coord_X = (x / MIDA_CASELLA) * MIDA_CASELLA;
	int coord_Y = (y / MIDA_CASELLA) * MIDA_CASELLA;

	return coord { coord_X, coord_Y };
}
