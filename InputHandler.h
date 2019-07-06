#pragma once
#include "Player.h"
#include "ClickAction.h"
#include "KeyboardAction.h"
#include <queue>
#include <utility>


class InputHandler
{
public:
	InputHandler() : human(nullptr), machine(nullptr) {}
	~InputHandler() {}
	void init(Player* h, Player* m);
	SDL_Event captureEvent();
	Action* processInput();
	
	bool isReady() const { return (human != nullptr && machine != nullptr); }

private:
	Player* human;
	Player* machine;
	std::vector<SDL_Event> eventRecord;

	coord getPosClicked(const SDL_Event& e) const;
	SDL_Scancode getKeyPressed(const SDL_Event& e) const;
	bool inputIsRelevant(const SDL_Event& e) const { return e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN; }
	Action* processEvent(const const SDL_Event& e) const;
};

