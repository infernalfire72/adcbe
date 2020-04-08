#pragma once

#include <string>
#include <cstring>
#include <vector>

class Packet {
public:
	short Id;
	std::vector<unsigned char> Data;

	Packet& operator << (const char* v) {
		return (*this) << std::string(v);
	}

	Packet& operator << (const std::string & v) {
		int size = v.size();
		if (!size)
			return (*this) << false;

		Data.emplace_back((char)11);

		for (; size >= 127; size -= 127)
			Data.push_back(128);

		Data.push_back(size);

		Data.resize(Data.size() + v.size());
		memcpy(&Data[Data.size() - v.size()], &v[0], v.size());
		return *this;
	}

	template<typename T>
	Packet& operator << (const T& v) {
		Data.resize(Data.size() + sizeof(T));
		memcpy(&Data[Data.size() - sizeof(T)], &v, sizeof(T));
		return *this;
	}

	Packet(short id) {
		Id = id;
		Data.reserve(128);
	}
};