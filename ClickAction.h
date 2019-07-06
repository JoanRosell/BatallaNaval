#pragma once
#include "Utilities.h"
#include "Action.h"
#include "Player.h"

/*
*	Accion que realiza un jugador, se generan exclusivamente a partir de eventos
*	Al formar parte de una jerarquia de clases se debe implementar el patron Clone
*	para asegurar una correcta copia. 
*
*	No se sobrecarga el ctor de copia ya que no necesitamos 
*	realizar deep copy, mas adelante se detalla por que
*/
class ClickAction : public Action
{
public:
	ClickAction() = delete; //	No tiene sentido permitir este constructor
	ClickAction(Player* source, Player* target, const coord& coordClicked);
	~ClickAction() {} // Destacar que NO se destruyen los objetos Player, el lifetime de este objeto es menor

	ActionOutcome execute();
	const coord& getParameter() const { return parameter; }

	/*	Clone pattern:
	*	Al contrario que en la mayoria de casos, aqui no se reliza deep copy.
	*	Esto se debe a que NO queremos copias del objeto Player al que estamos apuntando,
	*	solo queremos copiar el puntero para mantener su referencia
	*/
	Action* clone() { return new ClickAction(*this); } 
private:
	Player* source;
	Player* target;
	coord parameter;
};

