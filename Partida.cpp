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
	std::ofstream humanOutput("tauler_huma.txt");
	int elementsLogged(0);
	for (const auto& spriteType : ui.getHumanBoard())
	{
		if (spriteType == Sprite_Type::SHIP || spriteType == Sprite_Type::DAMAGED_SHIP)
			humanOutput << "1 ";
		else
			humanOutput << "0 ";
		elementsLogged++;

		if (elementsLogged == 10)
		{
			humanOutput << "\n";
			elementsLogged = 0;
		}
	}
	
	humanOutput.close();

	std::ofstream machineOutput("tauler_ordinador.txt");
	for (const auto& spriteType : ui.getMachineBoard())
	{
		if (spriteType == Sprite_Type::SHIP || spriteType == Sprite_Type::DAMAGED_SHIP)
			machineOutput << "1 ";
		else
			machineOutput << "0 ";
		elementsLogged++;

		if (elementsLogged == 10)
		{
			machineOutput << "\n";
			elementsLogged = 0;
		}
	}
	machineOutput.close();
	
}
