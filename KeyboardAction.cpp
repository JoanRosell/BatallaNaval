#include "KeyboardAction.h"

KeyboardAction::~KeyboardAction()
{
}

ActionOutcome KeyboardAction::execute()
{
	ActionOutcome outcome;

	if (keyCode == SDL_SCANCODE_ESCAPE)
		outcome.outcomeType = Outcome_Type::EXIT;

	return outcome;
}
