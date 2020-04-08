#pragma once

#include <vector>
#include "Player.h"

class Channel {
	std::string Name;
	std::string Topic;
	std::vector<Player*> Players;
};