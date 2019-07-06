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

	bool gameReady = game.isReady();
	
	if (!modeGrafic && gameReady)
	{
		game.dumpToFile();
		return;
	}

	if (gameReady)
	{
		bool gameEnded(false);

		do
		{
			game.drawGraphics();
			game.update();
			game.catchEvents();
			game.run();
			gameEnded = game.isFinished();
		} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !gameEnded);
	}
		
	// Sortim del bucle si pressionem ESC
}
