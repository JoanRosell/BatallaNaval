#include "Partida.h"



Partida::Partida()
{
	/*humanPlayer = Player(Player_Type::HUMAN);
	artificialPlayer = Player(Player_Type::MACHINE);*/
}


Partida::~Partida()
{
}

bool Partida::init(const std::string & initFileHuman, const std::string & initFileArtificial)
{
	bool dataInitialized(false);
	bool humanReady(false);
	bool aiReady(false);

	playerListener.init(&humanPlayer, &artificialPlayer);
	humanReady = humanPlayer.loadShipsFromFile(initFileHuman);
	aiReady = artificialPlayer.loadShipsFromFile(initFileArtificial);

	dataInitialized = humanReady && aiReady;

	if (dataInitialized)
		ui.init(humanPlayer.getShips(), artificialPlayer.getShips());
		
	return dataInitialized;
}

bool Partida::processEvents()
{
	ui.catchEvents();
	
	playerListener.waitForEvents();
	
	return false;
}

void Partida::drawGraphics()
{
	ui.printGraphics();
}

void Partida::update()
{
	ui.update();
}

void Partida::dumpToFile()
{
	logBoardToFile("tauler_huma.txt", ui.getHumanBoard());
	logBoardToFile("tauler_ordinador.txt", ui.getMachineBoard());
}

void Partida::playTurn()
{
	bool turnEnded(false);
	Outcome_Type result(Outcome_Type::UNDEFINED);

	while (!turnEnded)
	{
		if (humanPlayer.isActive())
		{
			playerListener.waitForEvents();
			
			Action* lastAction(playerListener.retrieveLastAction());

			if (!lastAction->isDone())
				result = lastAction->execute();
			

			if (result != Outcome_Type::INVALID)
			{
				switch (result)
				{
				case Outcome_Type::UNDEFINED:
					break;
				case Outcome_Type::WATER:
					ui.updateCell(lastAction->getParameter(), Sprite_Type::WATER, false);
					humanPlayer.endActionPhase();
					break;
				case Outcome_Type::SHIP_HIT:
					ui.updateCell(lastAction->getParameter(), Sprite_Type::DAMAGED_SHIP, false);
					break;
				case Outcome_Type::SHIP_DESTROYED:
					ui.updateShipStatus(lastAction->getAffectedShip(), false);
					break;
				default:
					break;
				}
				if (result != Outcome_Type::SHIP_HIT && result != Outcome_Type::SHIP_DESTROYED)
					

				turnEnded = true;
				
			}

			turn++;
		}
		else
		{
			// turno de la maquina
		}
					
	}
	
	
}

void Partida::logBoardToFile(const char * filename, const std::vector<Sprite_Type>& board)
{
	int elementsLogged(0);
	std::ofstream outFile(filename);

	for (const auto& spriteType : board)
	{
		if (spriteType == Sprite_Type::SHIP || spriteType == Sprite_Type::DAMAGED_SHIP)
			outFile << "1 ";
		else
			outFile << "0 ";
		elementsLogged++;

		if (elementsLogged == 10)
		{
			outFile << "\n";
			elementsLogged = 0;
		}
	}

	outFile.close();
}
