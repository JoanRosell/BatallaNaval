#include "InputHandler.h"

void InputHandler::init(Player * h, Player * m)
{
	if (human == nullptr && machine == nullptr)
	{
		if (h != nullptr && m != nullptr)
		{
			human = h;
			machine = m;
		}
		else
		{
			throw std::invalid_argument("Argument pointers not initialized!");
		}
	}
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

Action * InputHandler::processInput()
{
	return processEvent(captureEvent());
}

Action * InputHandler::processEvent(const SDL_Event & e) const
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		return new ClickAction(human, machine, getPosClicked(e));
	case SDL_KEYDOWN:
		return new KeyboardAction(human, getKeyPressed(e));
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