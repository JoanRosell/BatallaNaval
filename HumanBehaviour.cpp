#include "HumanBehaviour.h"

HumanBehaviour::~HumanBehaviour()
{
}

ActionOutcome HumanBehaviour::execute(Player * target) 
{
	if (!ih.isReady())
		ih.init(target);

	return ih.processInput()->execute();
}
