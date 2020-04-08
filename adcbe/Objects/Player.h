#pragma once

#include <string>

class Player {
public:
	int Id;
	std::string Username;
	std::string Token;

	Player();
	Player(const int& id, const std::string& name);

	~Player();
};