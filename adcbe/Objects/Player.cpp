#include "Player.h"
#include <string>
#include <cstring>
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
	Queue.reserve(512);
}

Player::~Player()
{

}

void Player::AddPacket(const Packet& p)
{
	queueMutex.lock();

	auto pos = Queue.size();
	auto pSize = p.Data.size();
	Queue.resize(pos + pSize + 7);
	memcpy(&Queue[pos], &p.Id, sizeof(short));
	memcpy(&Queue[pos + 3], &pSize, sizeof(int));
	memcpy(&Queue[pos + 7], &p.Data[0], pSize);

	queueMutex.unlock();
}

