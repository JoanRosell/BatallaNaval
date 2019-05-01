#include "joc.h"
#include "Ship.h"
#include "Player.h"
#include <iostream>
//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc()
{
	Screen pantalla(MIDA_X, MIDA_Y);
	pantalla.show();
	std::string iniFileHuman("C:\\dev\\BatallaNaval\\Program\\data\\vaixells_jugador_huma.txt");
	std::string iniFileArtificial("C:\\dev\\BatallaNaval\\Program\\data\\vaixells_jugador_ordinador.txt");

	do 
	{
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();
		
		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}
