#include "InputHandler.h"

Action * InputHandler::processInput()
{
	return processEvent(captureEvent());
}

SDL_Event InputHandler::captureEvent()
{
	bool eventCaptured(false);
	SDL_Event input;

	while (!eventCaptured)
	{
		if (SDL_WaitEvent(&input))
			if (inputIsRelevant(input))
			{
				eventRecord.push_back(input);
				eventCaptured = true;
			}	
	}
	
	return input;
}

Action * InputHandler::processEvent(const SDL_Event & e) const
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		return new ClickAction(owner, target, getPosClicked(e));
	case SDL_KEYDOWN:
		return new KeyboardAction(owner, getKeyPressed(e));
	default:
		throw std::invalid_argument("Invalid event type, check methods captureEvent() and inputIsRelevant()");
	}
}

coord InputHandler::getPosClicked(const SDL_Event& e) const
{
	return std::make_pair(e.button.x / MIDA_CASELLA, e.button.y / MIDA_CASELLA);
}

SDL_Scancode InputHandler::getKeyPressed(const SDL_Event & e) const
{
	return e.key.keysym.scancode;
}