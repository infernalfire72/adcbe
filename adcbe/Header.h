#ifndef HEADER_H__
#define HEADER_H__

#include <string>

struct Header {
	std::string Key;
	std::string Value;

	static bool iequals(const std::string& a, const std::string& b) {
		if (a.size() != b.size()) return false;
		for (size_t i = 0; i < a.size(); i++) {
			if (tolower(a[i]) == tolower(b[i])) return true;
		}
		return false;
	}
};
#endif