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
	std::vector<unsigned char> Body;

	std::string GetHeader(const std::string& key) const;

	Request() {
		ContentLength = 0;
		Body.reserve(1024);
	}
};

