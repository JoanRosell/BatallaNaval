#include "Partida.h"

Partida::Partida(const std::string & initFileHuman, const std::string & initFileArtificial) : humanPlayer(new HumanPlayer()), 
	machinePlayer(new MachinePlayer()), ready(false)
{
	if (humanPlayer->loadShipsFromFile(initFileHuman) && machinePlayer->loadShipsFromFile(initFileArtificial))
	{
		ready = true;
		ui.init(humanPlayer->getShips(), machinePlayer->getShips());
	}
}

void Partida::run()
{
	ActionOutcome outcome = playTurn();

	updateTurnState(outcome);
}

ActionOutcome Partida::playTurn()
{
	if (humanPlayer->isActive())
		return humanPlayer->takeActionAgainst(machinePlayer);
	else
		return machinePlayer->takeActionAgainst(humanPlayer);
}

void Partida::updateTurnState(ActionOutcome & outcome)
{
	if (outcome.outcomeType != Outcome_Type::INVALID)
	{
		if (outcome.outcomeType != Outcome_Type::EXIT)
		{
			if (outcome.outcomeType == Outcome_Type::WATER)
				passTurn();

			ui.updateChanges(outcome);
		}
		else
		{
			gameEnded = true;
		}
	}

	if (!gameEnded)
		if (machinePlayer->isActive())
		{
			if (humanPlayer->hasLost() || machinePlayer->hasLost())
				gameEnded = true;
			else
				passTurn();
		}
		else
		{
			if (machinePlayer->hasLost())
				passTurn();
		}
}

void Partida::passTurn()
{
	turn++;
	humanPlayer->updateTurn();
	machinePlayer->updateTurn();
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