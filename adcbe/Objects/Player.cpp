#include "Player.h"
#include <string>
#include <ctime>
#include "../Random.h"

Player::Player()
{
	Id = 0;
	Heartbeat = 0;
	Token = 0;
}

Player::Player(const int& id, const std::string& name)
{
	Id = id;
	Username = name;
	Heartbeat = std::time(nullptr);
	Token = Random::Long();
}

Player::~Player()
{
}

