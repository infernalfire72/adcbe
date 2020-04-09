#ifndef ADCBE__BANCHO__GLOBAL__
#define ADCBE__BANCHO__GLOBAL__

#include <mutex>
#include <vector>
#include "../Objects/Channel.h"
#include "../Objects/Player.h"

#ifdef _WIN32
inline std::vector<Player*> Players;
inline std::vector<Channel*> Channels;
#elif defined(__linux__) || defined(__CYGWIN__)
std::vector<Player*> Players;
std::vector<Channel*> Channels;
#endif

static std::mutex playerMutex;
static std::mutex channelMutex;

class Global {
public:
	static void AddPlayer(Player*& p) {
		playerMutex.lock();
		Players.emplace_back(p);
		playerMutex.unlock();
	}

	static Player* GetPlayer(const unsigned long long& token) {
		playerMutex.lock();
		for (auto& i : Players) {
			if (i->Token == token) {
				playerMutex.unlock();
				return i;
			}
		}
		playerMutex.unlock();
		return nullptr;
	}

	static Player* GetPlayer(const std::string& name) {
		playerMutex.lock();
		for (auto& i : Players) {
			if (i->Username == name) {
				playerMutex.unlock();
				return i;
			}
		}
		playerMutex.unlock();
		return nullptr;
	}

	static Player* GetPlayer(const int& id) {
		playerMutex.lock();
		for (auto& i : Players) {
			if (i->Id == id) {
				playerMutex.unlock();
				return i;
			}
		}
		playerMutex.unlock();
		return nullptr;
	}

};
#endif