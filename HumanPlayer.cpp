#include "HumanPlayer.h"



HumanPlayer::HumanPlayer() : Player()
{
	attacking = true;
	buildAttackCoords();
}


HumanPlayer::~HumanPlayer()
{
}

bool HumanPlayer::loadShipsFromFile(const std::string & filename)
{
	if (!fleet.empty())
		fleet.clear();
	
	bool shipsLoaded(false);
	std::string line;
	std::ifstream file;

	/*	Lectura de fichero:
	*		Para leer un fichero extraemos una linea entera
	*		y la transformamos en un input-stringstream para poder tratarla
	*		como un iostream (cout, cin, cerr, etc...) generico
	*/

	file.open(filename);

	/*
		getline(istream&, string&) retorna istream&, pero cuando
		usamos esta funcion en un ambito logico automaticamente testea los flags
		del istream, devolviendo un valor valido si el stream esta listo para operaciones de lectura
	*/
	while (std::getline(file, line))
	{
		std::istringstream shipData(line);
		int x;
		shipData >> x;
		int y;
		shipData >> y;
		int size;
		shipData >> size;
		/*
			Podriamos extraer la orientacion como un bool,
			pero seria mas complicado transformarlo a una orientacion valida
		*/
		int orientation;
		shipData >> orientation;
		//	Como orientation es un int debemos hacer un cast a Ship_Orientation para poder construir el barco
		//	Las coordenadas son un rango [1, 10], necesitamos transformar este rango a [0, 9]

		y += 10; // Movemos 10 posiciones hacia abajo los barcos para que queden en el tablero correcto

		fleet.emplace_back(--x, --y, size, (Ship_Orientation)orientation);
	}
	file.close();

	shipsAlive = fleet.size();

	if (shipsAlive == 10)
	{
		shipsLoaded = true;
		attacking = true;
	}

	return shipsLoaded;
}

ActionOutcome HumanPlayer::takeActionAgainst(Player* target)
{
	ActionOutcome outcome;

	if (!inputHandler.isReady())
		inputHandler.init(this, target);

	if (inputHandler.waitForEvents())
	{
		Action* lastAction(inputHandler.retrieveLastAction());

		if (lastAction != nullptr)
			if (!lastAction->isDone())
			{
				outcome = lastAction->execute();
				inputHandler.updateActionQueue();
			}
	}

	return outcome;
}

void HumanPlayer::buildAttackCoords()
{
	{
		int startX(0);
		int startY(0);

		for (int i = 0; i < k_nCoords; i++)
		{
			coord c(startX, startY);
			atkCoords.emplace(std::make_pair(c, false));

			startX++;

			if (startX > 9)
			{
				startY++;
				startX = 0;
			}
		}
	}
}

