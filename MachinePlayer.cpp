#include "MachinePlayer.h"



MachinePlayer::MachinePlayer() : Player(), distribution(0, 9), rng(device()), targetAcquired(false), currentAttackPattern(Ship_Orientation::UNDEFINED)
{
	buildAttackCoords();
}

void MachinePlayer::buildAttackCoords()
{
	int startX(0);
	int startY(10);

	for (int i = 0; i < k_nCoords; i++)
	{
		coord c(startX, startY);
		atkCoords.emplace(std::make_pair(c, false));

		startX++;

		if (startX > 9)
		{
			startY++;
			startX = 0;
		}
	}
}

ActionOutcome MachinePlayer::takeActionAgainst(Player * target)
{
	ActionOutcome outcome;
	coord atkCoord;

	if (!atkQueue.empty())
	{
		atkCoord = atkQueue.front();
		atkQueue.pop();
	}
	else
		atkCoord = makeRandomAttack();

	Action* currentAction(new ClickAction(this, target, atkCoord));
	outcome = currentAction->execute();

	if (outcome.outcomeType == Outcome_Type::SHIP_HIT)
	{
		if (!atkQueue.empty())
		{
			if (!targetAcquired)
				acquireTarget(outcome.coord);
		}
		else
			buildAttackQueue(outcome.coord);

		lastHitCoord = outcome.coord;
	}

	if (outcome.outcomeType == Outcome_Type::SHIP_DESTROYED)
	{
		targetAcquired = false;
		lastHitCoord = outcome.coord;
	}

	if (outcome.outcomeType == Outcome_Type::WATER && targetAcquired)
		updateAttackPattern(outcome.coord);

	return outcome;
}

coord MachinePlayer::makeRandomAttack()
{
	int randX(distribution(rng));
	int randY(distribution(rng));
	randY += 10;

	coord randAtkCoord{ randX, randY };

	while (!canAttackAt(randAtkCoord))
	{
		randX = distribution(rng);
		randY = distribution(rng);
		randY += 10;

		randAtkCoord.first = randX;
		randAtkCoord.second = randY;
	}

	return randAtkCoord;
}

void MachinePlayer::acquireTarget(const coord & c)
{
	targetAcquired = true;

	int deltaX(c.first - lastHitCoord.first);

	if (deltaX != 0)
	{
		if (deltaX < 0)
			currentAttackPattern = Ship_Orientation::LEFT;
		else
			currentAttackPattern = Ship_Orientation::RIGHT;
	}
	else
	{
		int deltaY(c.second - lastHitCoord.second);

		if (deltaY != 0)
			if (deltaY < 0)
				currentAttackPattern = Ship_Orientation::TOP;
			else
				currentAttackPattern = Ship_Orientation::BOTTOM;
	}

	buildAttackQueue(c);
}

void MachinePlayer::buildAttackQueue(const coord & c)
{
	if (!atkQueue.empty())
		clearQueue();

	switch (currentAttackPattern)
	{
	case Ship_Orientation::TOP:
		atkQueue.push({ c.first, c.second - 1 });
		atkQueue.push({ c.first, c.second - 2 });
		break;
	case Ship_Orientation::RIGHT:
		atkQueue.push({ c.first + 1, c.second });
		atkQueue.push({ c.first + 2, c.second });
		break;
	case Ship_Orientation::BOTTOM:
		atkQueue.push({ c.first, c.second + 1 });
		atkQueue.push({ c.first, c.second + 2 });
		break;
	case Ship_Orientation::LEFT:
		atkQueue.push({ c.first - 1, c.second });
		atkQueue.push({ c.first - 2, c.second });
		break;
	case Ship_Orientation::UNDEFINED:
		atkQueue.push({ c.first, c.second - 1 });
		atkQueue.push({ c.first + 1, c.second });
		atkQueue.push({ c.first - 1, c.second });
		atkQueue.push({ c.first, c.second + 1 });
		break;
	}
}

void MachinePlayer::clearQueue()
{
	std::queue<coord> empty;
	std::swap(atkQueue, empty);
}

void MachinePlayer::updateAttackPattern(const coord & c)
{
	switch (currentAttackPattern)
	{
	case Ship_Orientation::TOP:
		currentAttackPattern = Ship_Orientation::BOTTOM;
		break;
	case Ship_Orientation::RIGHT:
		currentAttackPattern = Ship_Orientation::LEFT;
		break;
	case Ship_Orientation::BOTTOM:
		currentAttackPattern = Ship_Orientation::TOP;
		break;
	case Ship_Orientation::LEFT:
		currentAttackPattern = Ship_Orientation::RIGHT;
		break;
	}

	buildAttackQueue(c);
}

bool MachinePlayer::loadShipsFromFile(const std::string & filename)
{
	if (!fleet.empty())
		fleet.clear();

	bool shipsLoaded(false);
	std::string line;
	std::ifstream file;

	/*	Lectura de fichero:
	*		Para leer un fichero extraemos una linea entera
	*		y la transformamos en un input-stringstream para poder tratarla
	*		como un iostream (cout, cin, cerr, etc...) generico
	*/

	file.open(filename);

	/*
		getline(istream&, string&) retorna istream&, pero cuando
		usamos esta funcion en un ambito logico automaticamente testea los flags
		del istream, devolviendo un valor valido si el stream esta listo para operaciones de lectura
	*/
	while (std::getline(file, line))
	{
		std::istringstream shipData(line);
		int x;
		shipData >> x;
		int y;
		shipData >> y;
		int size;
		shipData >> size;
		/*
			Podriamos extraer la orientacion como un bool,
			pero seria mas complicado transformarlo a una orientacion valida
		*/
		int orientation;
		shipData >> orientation;
		//	Como orientation es un int debemos hacer un cast a Ship_Orientation para poder construir el barco
		//	Las coordenadas son un rango [1, 10], necesitamos transformar este rango a [0, 9]
		
		fleet.emplace_back(--x, --y, size, (Ship_Orientation)orientation);
	}
	file.close();

	shipsAlive = fleet.size();

	if (shipsAlive == 10)
	{
		shipsLoaded = true;
		attacking = false;
	}

	return shipsLoaded;
}