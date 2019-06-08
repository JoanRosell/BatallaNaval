#include "Partida.h"



Partida::Partida()
{
	/*humanPlayer = Player(Player_Type::HUMAN);
	artificialPlayer = Player(Player_Type::MACHINE);*/
}


Partida::~Partida()
{
}

Partida::Partida(const std::string & initFileHuman, const std::string & initFileArtificial) : humanPlayer(new HumanPlayer()), 
	machinePlayer(new MachinePlayer()), ready(false)
{
	bool humanReady(false);
	bool machineReady(false);

	humanReady = humanPlayer->loadShipsFromFile(initFileHuman);
	machineReady = machinePlayer->loadShipsFromFile(initFileArtificial);

	ready = humanReady && machineReady;

	if (ready)
		ui.init(humanPlayer->getShips(), machinePlayer->getShips());
}

void Partida::catchEvents()
{
	ui.catchEvents();
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

void Partida::playTurn()
{
	ActionOutcome outcome;

	if (humanPlayer->isActive())
		outcome = humanPlayer->takeAction(machinePlayer);
	else 
		if (machinePlayer->isActive())
			outcome = machinePlayer->takeAction(humanPlayer);

	if (outcome.outcomeType != Outcome_Type::INVALID)
		ui.updateChanges(outcome);
		

	if (machinePlayer->isActive())
	{
		bool humanDefeated(humanPlayer->getShipsAlive() == 0);
		bool machineDefeated(machinePlayer->getShipsAlive() == 0);

		if (humanDefeated || machineDefeated)
		{
			gameEnded = true;
		}
	}

	turn++;
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