#ifndef ADCBE__BANCHO__GLOBAL__
#define ADCBE__BANCHO__GLOBAL__

#include <ctime>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include "../Objects/Channel.h"
#include "../Objects/Player.h"

inline std::vector<Player*> Players;
inline std::vector<Channel*> Channels;

static std::shared_mutex playerMutex;
static std::shared_mutex channelMutex;

class Global {
public:
	static void CheckPlayerTimeout() {
		std::lock_guard<std::shared_mutex> lock(playerMutex);

		for (size_t i = 0; i < Players.size(); i++) {
			if (std::time(nullptr) - Players[i]->Heartbeat > 50000) {
				delete Players[i];
				Players.erase(Players.begin() + i);
				i--;
			}
		}
	}

	static void AddPlayer(Player*& p) {
		std::lock_guard<std::shared_mutex> lock(playerMutex);
		Players.emplace_back(p);
	}

	static Player* GetPlayer(const unsigned long long& token) {
		std::shared_lock<std::shared_mutex> lock(playerMutex);
		for (auto& i : Players) {
			if (i->Token == token) {
				return i;
			}
		}
		return nullptr;
	}

	static Player* GetPlayer(const std::string& name) {
		std::shared_lock<std::shared_mutex> lock(playerMutex);
		for (auto& i : Players) {
			if (i->Username == name) {
				return i;
			}
		}
		return nullptr;
	}

	static Player* GetPlayer(const int& id) {
		std::shared_lock<std::shared_mutex> lock(playerMutex);
		for (auto& i : Players) {
			if (i->Id == id) {
				return i;
			}
		}

		return nullptr;
	}

	static void AddChannel(const std::string& Name, const std::string& Topic) {
		auto c = new Channel(Name, Topic);
		Channels.emplace_back(c);
	}

	static void Broadcast(const Packet& p) {
		for (auto& i : Players) {
			*i << p;
		}
	}

	static void SetupChannels() {
		AddChannel("#osu", "Main osu! Channel");
		AddChannel("#announce", "Announcements Channel");
	}
};
#endif