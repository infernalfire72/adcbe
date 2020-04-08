#pragma once

#include <string>
#include <vector>
#include "Header.h"

class Request
{
public:
	std::string URI;
	std::string Method;
	Header Headers[16];
	unsigned long long ContentLength;
	char* payload_start;

	std::vector<char> Body();
	std::string GetHeader(const std::string& key) const;

	Request() {
		payload_start = nullptr;
		ContentLength = 0;
	}
};

