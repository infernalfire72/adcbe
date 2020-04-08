#pragma once

#include "../../Request.h"
#include "../../Response.h"
#include "../../Objects/Player.h"

#include "../Packets/Packets.h"

void LoginEvent(const Request& req, Response& res) {

	Player *p = new Player(1337, "Nexus");
	p->Token = "hi-c++";

	res.SetHeader("cho-token", p->Token);
	
	res.Write(Packets::LoginReply(p->Id));

	res.Write(Packets::Announce("test"));

	Players.emplace_back(p);

	res.EndResponse(200);
}