#include "Player.h"
#include <string>

Player::Player()
{
	Id = 0;
}

Player::Player(const int& id, const std::string& name)
{
	Id = id;
	Username = name;
}

Player::~Player()
{
}

