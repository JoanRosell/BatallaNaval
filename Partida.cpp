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
	
	return false;
}
