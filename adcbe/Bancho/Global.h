#pragma once

#include <vector>
#include "../Objects/Channel.h"
#include "../Objects/Player.h"

inline std::vector<Player*> Players;
inline std::vector<Channel*> Channels;

class Global {
public:
	static Player* GetPlayer(std::string token) {
		for (auto& i : Players) 
			if (i->Token == token)
				return i;

		return nullptr;
	}
};