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

            for (long long i = 0; i + 6 < req.ContentLength; ) {
                auto Id = *(short*)(&req.Body[i]);
                i += 3;
                auto Length = *(int*)(&req.Body[i]);
                i += 4;

                std::vector<unsigned char> Data;
                if (Length) {
                    Data.resize(Length);
                    memcpy(&Data[0], &req.Body[i], Length);
                    i += Length;
                }

                switch (Id) {
                default:
                    std::cout << "Unhandled Event " << Id << " L" << Data.size() << std::endl;
                }
            }
        }

        ROUTE_GET(/) {

        }

        ROUTE_END
    }
};