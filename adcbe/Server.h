#pragma once

#include "Request.h"
#include "Response.h"

#if defined(__linux__) || defined(__CYGWIN__)
#include <unistd.h>
#include "Linux.h"
#endif

#define ROUTE_START if(0){}
#define ROUTE(url, method) else if (#url == req.URI && #method == req.Method)
#define ROUTE_GET(url) ROUTE(url, GET)
#define ROUTE_POST(url) ROUTE(url, POST)
#define ROUTE_END else { send(res.clientSocket, "HTTP/1.1 404 Not Found\r\n\r\nPage not found.", 41, 0); }

class Server
{
public:
	int start_server(const unsigned short& port);
	virtual void processRequest(const Request& req, Response& res) {
        ROUTE_START

        ROUTE_GET(/) {
            res.Write("Hello There!\r\n");
            res.Write("FrostiEats v1\r\n");
            res.Write(req.GetHeader("User-Agent"));
        }

        ROUTE_END
	}
};

