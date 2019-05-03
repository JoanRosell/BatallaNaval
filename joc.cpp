#include "joc.h"
#include "Partida.h"
#include <iostream>

//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc(bool modeGrafic)
{
	Partida game;
	std::string iniFileHuman("vaixells_jugador_huma.txt");
	std::string iniFileArtificial("vaixells_jugador_ordinador.txt");
	game.init(iniFileHuman, iniFileArtificial);
	
	if (!modeGrafic)
	{
		game.dumpToFile();
		return;
	}

	Screen pantalla(MIDA_X, MIDA_Y);
	pantalla.show();

	do 
	{
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();
		
		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}
