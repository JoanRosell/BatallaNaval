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

	humanPlayer.initAtkCoords(Player_Type::HUMAN);
	machinePlayer.initAtkCoords(Player_Type::MACHINE);

	playerListener.init(&humanPlayer, &machinePlayer);
	humanReady = humanPlayer.loadShipsFromFile(initFileHuman);
	aiReady = machinePlayer.loadShipsFromFile(initFileArtificial);

	dataInitialized = humanReady && aiReady;

	if (dataInitialized)
		ui.init(humanPlayer.getShips(), machinePlayer.getShips());
		
	return dataInitialized;
}

void Partida::processEvents()
{
	ui.catchEvents();
	
	playerListener.waitForEvents();
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
	/*logBoardToFile("tauler_huma.txt", ui.getHumanBoard());
	logBoardToFile("tauler_ordinador.txt", ui.getMachineBoard());*/
}

void Partida::playTurn() // TO REFACTOR
{
	bool turnEnded(false);
	if (humanPlayer.isActive())
	{			
		Action* lastAction(playerListener.retrieveLastAction());

		if (lastAction != nullptr)
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
					}

					turn++;
					turnEnded = true;
				}
			}
	}
	else
	{
		

		if (humanPlayer.getShipsAlive() == 0 || machinePlayer.getShipsAlive() == 0)
		{
			// Turn ended
		}
	}	
}

void Partida::logBoardToFile(const char * filename, const std::vector<VisualizationCell>& board)
{
	int elementsLogged(0);
	std::ofstream outFile(filename);

	for (const auto& vCell : board)
	{
		if (vCell.spriteType == Sprite_Type::SHIP || vCell.spriteType == Sprite_Type::SHIP_HIT)
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