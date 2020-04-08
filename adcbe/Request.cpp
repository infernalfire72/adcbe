#include "Request.h"

std::vector<char> Request::Body()
{
	return std::vector<char>(payload_start, payload_start + ContentLength);
}

std::string Request::GetHeader(const std::string& key) const
{
    for (auto& i : Headers)
        if (Header::iequals(i.Key, key))
            return i.Value;

    return std::string("");
}
