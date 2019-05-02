#include "joc.h"
#include "Partida.h"
#include <iostream>

//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc(bool modeGrafic)
{
	Screen pantalla(MIDA_X, MIDA_Y);
	pantalla.show();
	std::string iniFileHuman("Program\\data\\vaixells_jugador_huma.txt");
	std::string iniFileArtificial("Program\\data\\vaixells_jugador_ordinador.txt");
	
	Partida game;
	game.init(iniFileHuman, iniFileArtificial);	

	do 
	{
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();
		
		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}
