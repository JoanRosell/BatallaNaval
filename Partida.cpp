#include "Partida.h"

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

void Partida::runTurn() 
{
	ActionOutcome outcome;

	if (humanPlayer->isActive())
		outcome = humanPlayer->takeActionAgainst(machinePlayer);
	else 
		if (machinePlayer->isActive())
			outcome = machinePlayer->takeActionAgainst(humanPlayer);

	if (outcome.outcomeType != Outcome_Type::EXIT)
	{
		if (outcome.outcomeType == Outcome_Type::WATER)
			if (humanPlayer->isActive())
			{
				turn++;
				machinePlayer->startAttack();
				humanPlayer->endAttack();
			}
			else
				if (machinePlayer->isActive())
				{
					turn++;
					humanPlayer->startAttack();
					machinePlayer->endAttack();
				}


		if (outcome.outcomeType != Outcome_Type::INVALID)
			ui.updateChanges(outcome);

		bool machineDefeated(machinePlayer->getShipsAlive() == 0);
		bool humanDefeated(humanPlayer->getShipsAlive() == 0);

		if (machineDefeated && turn == 0)
		{
			turn++;
			machinePlayer->startAttack();
			humanPlayer->endAttack();
		}

		if (machinePlayer->isActive())
			if (humanDefeated || machineDefeated)
				gameEnded = true;
	}
	else
		gameEnded = true;
	
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