#ifdef __linux__ // actual brain mode
#include <vector>
#include "../Objects/Channel.h"
#include "../Objects/Player.h"
#endif

#ifndef ADCBE__BANCHO__GLOBAL__
#define ADCBE__BANCHO__GLOBAL__

#ifdef _WIN32
#include <vector>
#include "../Objects/Channel.h"
#include "../Objects/Player.h"

inline std::vector<Player*> Players;
inline std::vector<Channel*> Channels;
#elif defined(__linux__)
std::vector<Player*> Players;
std::vector<Channel*> Channels;
#endif

class Global {
public:
	static Player* GetPlayer(std::string token) {
		for (auto& i : Players) 
			if (i->Token == token)
				return i;

		return nullptr;
	}
};
#endif