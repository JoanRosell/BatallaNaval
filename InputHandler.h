#pragma once
#include "Player.h"
#include "ClickAction.h"
#include "KeyboardAction.h"
#include <utility>

class InputHandler
{
public:
	InputHandler() : human(nullptr), machine(nullptr) {}
	~InputHandler() {}

	void init(Player* h, Player* m);
	Action* processInput();
	
	bool isReady() const { return (human != nullptr && machine != nullptr); }

private:
	Player* human;
	Player* machine;
	std::vector<SDL_Event> eventRecord;

	Action* processEvent(const SDL_Event& e) const;
	SDL_Event captureEvent();
	bool inputIsRelevant(const SDL_Event& e) const { return e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN; }
	coord getPosClicked(const SDL_Event& e) const;
	SDL_Scancode getKeyPressed(const SDL_Event& e) const;
};