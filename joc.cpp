#include "joc.h"
#include <iostream>
//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc(bool mode)
{
	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(MIDA_X, MIDA_Y);

	//Mostrem la finestra grafica
	pantalla.show();

	// ********************************************
	// AFEGIR CODI: Crear tots els grafics del joc
	//				Inicialitzar variables posicio vaixell
	// ********************************************
	Sprite ship("C:\\dev\\BatallaNaval\\Program\\data\\vaixell.png");
	Sprite board("C:\\dev\\BatallaNaval\\Program\\data\\caselles.png");
	int grid_X = 0;
	int grid_Y = 0;
	do
	{
		// Captura tots els events de ratol� i teclat de l'ultim cicle
		pantalla.processEvents();


		// *****************************************************************************
		// AFEGIR CODI:	Capturar si s'ha fet clic amb el ratol�
		//				Si s'ha fet clic amb el ratol� modificar posici� (fila i columna del tauler) 
		//				del vaixell en funci� de la posici� del ratol�
		// *****************************************************************************
		if (Mouse_getButLeft())
		{
			grid_X = ((int)Mouse_getX() / MIDA_CASELLA) * MIDA_CASELLA;
			grid_Y = ((int)Mouse_getY() / MIDA_CASELLA) * MIDA_CASELLA;
		}
		// *****************************************************************************
		// AFEGIR CODI: Redibuixar tauler 
		//				Dibuixar el vaixell a la posici� (fila i columna) que toqui						
		// *****************************************************************************
		board.draw(INI_PANTALLA_X, INI_PANTALLA_Y);
		ship.draw(grid_X, grid_Y);
		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC
}
