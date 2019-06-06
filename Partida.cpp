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

	playerListener.init(&humanPlayer, &machinePlayer);
	humanReady = humanPlayer.loadShipsFromFile(initFileHuman);
	aiReady = machinePlayer.loadShipsFromFile(initFileArtificial);

	dataInitialized = humanReady && aiReady;

	if (dataInitialized)
		ui.init(humanPlayer.getShips(), machinePlayer.getShips());
		
	return dataInitialized;
}

bool Partida::processEvents()
{
	ui.catchEvents();
	
	return playerListener.waitForEvents();
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

	while (!turnEnded)
	{
		if (humanPlayer.isActive())
		{			
			Action* lastAction(playerListener.retrieveLastAction());

			if (!lastAction->isDone())
			{
				ActionOutcome outcome = lastAction->execute();

				if (outcome.outcomeType != Outcome_Type::INVALID)
				{
					ui.updateChanges(outcome);

					if (outcome.outcomeType == Outcome_Type::WATER)
					{
						humanPlayer.endActionPhase();
						machinePlayer.startActionPhase();
						turnEnded = true;
					}

					turn++;
					
				}
			}
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