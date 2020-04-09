#pragma once

#include <string>

class Player {
public:
	int Id;
	std::string Username;
	unsigned long long Token;
	long long Heartbeat;

	Player();
	Player(const int& id, const std::string& name);

	~Player();
};