#pragma once
#include <utility>
#include <vector>
#include "joc.h"
#include "Utilities.h"
#include "KeyboardAction.h"
#include "ClickAction.h"

class Player;

class InputHandler
{
public:
	InputHandler(Player* p) : owner(p), target(nullptr) {}
	~InputHandler() {}

	void init(Player* p) { target = p; }
	Action* processInput();
	
	bool isReady() const { return target != nullptr; }

private:
	Player* owner;
	Player* target;
	std::vector<SDL_Event> eventRecord;

	Action* processEvent(const SDL_Event& e) const;
	SDL_Event captureEvent();
	bool inputIsRelevant(const SDL_Event& e) const { return e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN; }
	coord getPosClicked(const SDL_Event& e) const;
	SDL_Scancode getKeyPressed(const SDL_Event& e) const;
};