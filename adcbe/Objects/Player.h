#pragma once

#include <string>
#include <mutex>
#include <vector>
#include "../Response.h"
#include "../Bancho/Packets/Packet.h"

class Player {
public:
	int Id;
	std::string Username;
	unsigned long long Token;
	long long Heartbeat;

	std::vector<unsigned char> Queue;

	Player();
	Player(const int& id, const std::string& name);

	~Player();

	Player& operator << (const Packet& p) {
		AddPacket(p);
		return *this;
	}

	void AddPacket(const Packet& p);
	void WriteTo(Response& r) {
		queueMutex.lock();

		r.Write(Queue);
		Queue.resize(0);

		queueMutex.unlock();
	}
private:
	std::mutex queueMutex;
};