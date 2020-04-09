#include "Player.h"
#include <string>
#include <ctime>

Player::Player()
{
	Id = 0;
}

Player::Player(const int& id, const std::string& name)
{
	Id = id;
	Username = name;
	Heartbeat = std::time(nullptr);
}

Player::~Player()
{
}

