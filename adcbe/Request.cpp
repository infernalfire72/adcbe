#include "Request.h"

std::string Request::GetHeader(const std::string& key) const
{
    for (auto& i : Headers)
        if (Header::iequals(i.Key, key))
            return i.Value;

    return std::string("");
}
