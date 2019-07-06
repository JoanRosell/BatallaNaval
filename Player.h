#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Utilities.h"

class Player
{
public:
	Player();
	virtual ~Player() {}

	//	Accessors
	bool isActive() const { return attacking; }
	int getShipsAlive() const { return shipsAlive; }
	bool fleetIsHit(const coord& c) const;
	bool canAttackAt(const coord& c) const;

	void startAttack() { attacking = true; }
	void endAttack() { attacking = false; }

	void updateAtkCoords(const coord& c) { atkCoords.find(c)->second = true; }

	virtual bool loadShipsFromFile(const std::string& file) = 0;
	virtual ActionOutcome takeActionAgainst(Player* target) = 0;
	
	const std::vector<Ship>& getShips() const { return fleet; }

	Ship getLastShipHit() const { return *lastShipHit; }

	Outcome_Type processHit(const coord& c);

protected:
	int shipsAlive;
	bool attacking;

	std::vector<Ship> fleet;
	std::vector<Ship>::iterator lastShipHit;
	std::map<coord, bool> atkCoords;

	virtual void buildAttackCoords() = 0;

	static const int k_nCoords = 100;

private:
	void init();

	static const short kShipTypes = 4;
	static const short kMaxShipSize = 4;
	static const short kMinShipQuantity = 1;
	static const short kMaxShipsPerPlayer = 10;
	
};


inline Player::Player() : shipsAlive(0), attacking(false)
{
	init();
}

inline void Player::init()
{
	int nTypes(kShipTypes);
	int currentShipSize(kMaxShipSize);
	int currentShipsToBuild(kMinShipQuantity);

	fleet.reserve(kMaxShipsPerPlayer);

	for (int type = 0; type < nTypes; type++)
	{
		for (int i = 0; i < currentShipsToBuild; i++)
			fleet.emplace_back(currentShipSize);

		currentShipSize--;
		currentShipsToBuild++;
	}
}

inline bool Player::fleetIsHit(const coord & c) const
{
	bool shipHit(false);

	for (const auto& ship : fleet)
	{
		shipHit = ship.isHit(c);

		if (shipHit)
			break;
	}

	return shipHit;
}

inline bool Player::canAttackAt(const coord & c) const
{
	try 
	{
		return !atkCoords.at(c);
	}
	catch (const std::out_of_range& o)
	{
		return false;
	}
}

inline Outcome_Type Player::processHit(const coord & c)
{
	Outcome_Type oType(Outcome_Type::WATER);

	lastShipHit = std::find_if(fleet.begin(), fleet.end(), [&](const Ship& s) {
		return s.isHit(c);
	});

	if (lastShipHit != fleet.end())
	{
		lastShipHit->registerHit(c);
		if (lastShipHit->isDestroyed())
		{
			oType = Outcome_Type::SHIP_DESTROYED;
			--shipsAlive;
		}
		else
			oType = Outcome_Type::SHIP_HIT;
	}

	return oType;
}