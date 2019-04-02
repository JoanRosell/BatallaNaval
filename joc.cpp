#include "joc.h"
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
	do 
	{
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();
			
		// *****************************************************************************
		// AFEGIR CODI:	Capturar si s'ha fet clic amb el ratolí
		//				Si s'ha fet clic amb el ratolí modificar posició (fila i columna del tauler) 
		//				del vaixell en funció de la posició del ratolí
		// *****************************************************************************
		
		// *****************************************************************************
		// AFEGIR CODI: Redibuixar tauler 
		//				Dibuixar el vaixell a la posició (fila i columna) que toqui						
		// *****************************************************************************

		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}
