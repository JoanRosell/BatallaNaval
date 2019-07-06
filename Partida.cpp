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

void Partida::run() 
{
	ActionOutcome outcome = playTurn();

	updateUserInterface(outcome);

	if (!isLastTurn() && outcome.outcomeType != Outcome_Type::EXIT)
		passTurn();
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

ActionOutcome Partida::playTurn()
{
	if (humanPlayer->isActive())
		return humanPlayer->takeActionAgainst(machinePlayer);
	else
		return machinePlayer->takeActionAgainst(humanPlayer);
}

void Partida::passTurn()
{
	turn++;
	humanPlayer->updateTurn();
	machinePlayer->updateTurn();
}

void Partida::updateUserInterface(ActionOutcome & outcome)
{
	if (outcome.outcomeType != Outcome_Type::INVALID && outcome.outcomeType != Outcome_Type::EXIT)
		ui.updateChanges(outcome);
}
