#include "MachineBehaviour.h"

ActionOutcome MachineBehaviour::execute(Player* target)
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

	Action* currentAction(new ClickAction(owner, target, atkCoord));
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

coord MachineBehaviour::makeRandomAttack()
{
	int randX(distribution(rng));
	int randY(distribution(rng));
	randY += 10;

	coord randAtkCoord{ randX, randY };

	while (!owner->canAttackAt(randAtkCoord))
	{
		randX = distribution(rng);
		randY = distribution(rng);
		randY += 10;

		randAtkCoord.first = randX;
		randAtkCoord.second = randY;
	}

	return randAtkCoord;
}

void MachineBehaviour::acquireTarget(const coord & c)
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

void MachineBehaviour::buildAttackQueue(const coord & c)
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

void MachineBehaviour::clearQueue()
{
	std::queue<coord> empty;
	std::swap(atkQueue, empty);
}

void MachineBehaviour::updateAttackPattern(const coord & c)
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
