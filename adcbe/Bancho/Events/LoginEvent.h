#pragma once

#include "../../Request.h"
#include "../../Response.h"
#include "../../Objects/Player.h"

#include "../Packets/Packets.h"

void LoginEvent(const Request& req, Response& res) {

	Player *p = new Player(1337, "Nexus");

	res.SetHeader("cho-token", std::to_string(p->Token));
	
	res.Write(Packets::LoginReply(p->Id));

	res.Write(Packets::Announce("test"));

	Global::AddPlayer(p);

	res.EndResponse(200);
}