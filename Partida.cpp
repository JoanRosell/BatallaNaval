#include "Partida.h"



Partida::Partida()
{
}


Partida::~Partida()
{
}

bool Partida::init(const std::string & initFileHuman, const std::string & initFileArtificial)
{
	bool dataInitialized(false);
	bool humanReady(false);
	bool aiReady(false);

	humanReady = humanPlayer.loadShipsFromFile(initFileHuman);
	aiReady = artificialPlayer.loadShipsFromFile(initFileArtificial);

	dataInitialized = humanReady && aiReady;

	if (dataInitialized)
		ui.init(humanPlayer.getShips(), artificialPlayer.getShips());
		
	return dataInitialized;
}

void Partida::dumpToFile()
{
	logBoardToFile("tauler_huma.txt", ui.getHumanBoard());
	logBoardToFile("tauler_ordinador.txt", ui.getMachineBoard());
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
