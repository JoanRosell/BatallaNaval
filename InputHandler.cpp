#include "InputHandler.h"

void InputHandler::init(Player * h, Player * m)
{
	if (human != nullptr || machine != nullptr)
		return;
	else
	{
		human = h;
		machine = m;
		ready = true;
	}
}

bool InputHandler::waitForEvents()
{
	bool eventCaptured(false);

	while (!eventCaptured)
	{
		SDL_Event input;
		if (SDL_WaitEvent(&input))
		{
			if (input.type == SDL_MOUSEBUTTONDOWN)
			{
				coord coord(coordFromPixel(input.button.x, input.button.y));
				actions.push(new ClickAction(human, machine, coord));
				eventCaptured = true;
			}
			else
			{
				if (input.type == SDL_KEYDOWN)
				{
					actions.push(new KeyboardAction(human, input.key.keysym.scancode));
					eventCaptured = true;
				}
			}
		}
			
	}
	
	return eventCaptured;
}

Action * InputHandler::getLastAction()
{
	if (!actions.empty())
		return actions.front();
	else
		return nullptr;
		
}

void InputHandler::updateActionQueue()
{
	if (actions.front()->isDone())
		actions.pop();
}

coord InputHandler::coordFromPixel(int x, int y)
{
	int coord_X = x / MIDA_CASELLA;
	int coord_Y = y / MIDA_CASELLA;

	return std::make_pair(coord_X, coord_Y);
}
