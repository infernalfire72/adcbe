#pragma once

#include <vector>
#include "Player.h"

class Channel {
public:
	std::string Name;
	std::string Topic;
	std::vector<Player*> Players;

	Channel(const std::string& name, const std::string& topic);
};