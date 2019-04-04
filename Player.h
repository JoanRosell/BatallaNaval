#pragma once
class Player
{
public:
	Player();
	virtual ~Player();
	bool isDeploying() { return true; }
	bool isAttacking() { return true; }
protected:
private:

};



Player::Player()
{
}


Player::~Player()
{
}
