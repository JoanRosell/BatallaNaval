#include "joc.h"
#include "Ship.h"
#include <vector>
#include <iostream>
//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc()
{
	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(MIDA_X, MIDA_Y);
	//Mostrem la finestra grafica
	pantalla.show();
	
	
	// ********************************************
	// AFEGIR CODI: Crear tots els grafics del joc
	//				Inicialitzar variables posicio vaixell
	// ********************************************
	
	Sprite board("C:\\dev\\BatallaNaval\\Program\\data\\caselles.png");
	int grid_X = 0;
	int grid_Y = 0;
	
	Ship anotherShip("C:\\Dev\\BatallaNaval\\Program\\data\\vaixell.png", 4);
	const char* path = "C:\\dev\\BatallaNaval\\Program\\data\\vaixell.png";

	do 
	{
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();
					
		
		board.draw(INI_PANTALLA_X, INI_PANTALLA_Y);
		
		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}
