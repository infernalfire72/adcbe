#pragma once

#include "../Server.h"

#include "../Request.h"
#include "../Response.h"

class WebServer : public Server {
	void processRequest(const Request& req, Response& res) override {
		ROUTE_START

		ROUTE_GET(/web/osu-submit-modular-selector.php) {

		}

		ROUTE_GET(/) {
			res << "Web Front";
		}

		ROUTE_END
	}
};