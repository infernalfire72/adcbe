#pragma once

#include "Packet.h"
#include "../../Objects/Player.h"

class Packets {
public:
	static Packet LoginReply(const int& id) {
		return Packet(5) << id;
	}

	static Packet Logout(const int& id) {
		return Packet(12) << id;
	}

	static Packet Announce(const std::string& msg) {
		return Packet(24) << msg;
	}
};