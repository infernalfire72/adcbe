#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include "Header.h"

#ifdef _WIN32
#include <WinSock2.h>
#elif defined(__linux__) || defined(__CYGWIN__)
#include "linux.h"
#endif

#include "Bancho/Packets/Packet.h"

class Response {
public:
	bool w;
	SOCKET clientSocket;
	Response(SOCKET cSock);

	void EndResponse(int code);

	void Write(const std::string& value);
	void Write(const char* value);
	void Write(const Packet& p);

	template <typename T>
	void Write(const std::vector<T>& values);

	template <typename T>
	void Write(const T& value) {
		data.resize(data.size() + sizeof(T));
		memcpy(&data[data.size() - sizeof(T)], (void*)&value, sizeof(T));
	}

	template <typename T>
	Response& operator << (const T& value) {
		Write(value);
		return *this;
	}

	void SetHeader(const std::string& Key, const std::string& Value);
private:
	Header Headers[16];
	std::vector<unsigned char> data;
};