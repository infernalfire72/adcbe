#pragma once

#include "../Server.h"

#include "../Request.h"
#include "../Response.h"

#include "Global.h"

#include "Events/LoginEvent.h"
#include "Packets/Packets.h"

class BanchoServer : public Server {
    void processRequest(const Request& req, Response& res) override {
        ROUTE_START

        ROUTE_POST(/) {
            if (req.GetHeader("User-Agent") != "osu!") return;

            std::string Token = req.GetHeader("osu-token");

            if (!Token.size()) {
                LoginEvent(req, res);
                return;
            }

            auto p = Global::GetPlayer(Token);

            if (!p) {
                res.Write(Packets::LoginReply(-5));
                res.EndResponse(403);
                return;
            }

            std::cout << p->Username << std::endl;
        }

        ROUTE_GET(/) {

        }

        ROUTE_END
    }
};