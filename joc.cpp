#include "joc.h"
#include "Partida.h"
#include <iostream>

//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------

void joc(bool modeGrafic)
{
	std::string iniFileHuman("Program\\data\\vaixells_jugador_huma.txt");
	std::string iniFileArtificial("Program\\data\\vaixells_jugador_ordinador.txt");

	Partida game(iniFileHuman, iniFileArtificial);

	if (game.isReady())
	{
		do
		{
			game.drawGraphics();
			game.update();
			game.catchEvents();
			game.run();
		} while (!game.isFinished());
	}
}
