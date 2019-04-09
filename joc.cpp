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

	int maxDeployments = fleet.size();
	do 
	{
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();
					
		
<<<<<<< HEAD
		board.draw(INI_PANTALLA_X, INI_PANTALLA_Y);
		
=======
		// *****************************************************************************
		// AFEGIR CODI:	Capturar si s'ha fet clic amb el ratolí
		//				Si s'ha fet clic amb el ratolí modificar posició (fila i columna del tauler) 
		//				del vaixell en funció de la posició del ratolí
		// *****************************************************************************
		if (Mouse_getButLeft())
		{
			grid_X = ((int)Mouse_getX() / MIDA_CASELLA) * MIDA_CASELLA;
			grid_Y = ((int)Mouse_getY() / MIDA_CASELLA) * MIDA_CASELLA;

			if (deployedShips < maxDeployments)
			{
				fleet.at(deployedShips).deployAt(grid_X, grid_Y);
				deployedShips++;
			}
		}
		// *****************************************************************************
		// AFEGIR CODI: Redibuixar tauler 
		//				Dibuixar el vaixell a la posició (fila i columna) que toqui						
		// *****************************************************************************
		
		
		// Esto lo hace Board, que se encarga de la representación gráfica del juego
		board.draw(INI_PANTALLA_X, INI_PANTALLA_Y);
		for (const auto& ship : fleet)
			ship.draw();
>>>>>>> 660bc25525f14f3ab81b803c6936a270b8e5bd0f
		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}
