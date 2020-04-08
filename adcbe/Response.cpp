#include "Response.h"
#include "Bancho/Packets/Packet.h"

Response::Response(SOCKET cSock)
{
	clientSocket = cSock;
	data.reserve(512);
	w = false;
}

void Response::EndResponse(int code)
{
	w = 1;
	std::ostringstream strs;
	switch (code) {
	case 200:
		strs << "HTTP/1.1 200 OK\r\n";
		break;
	case 400:
		strs << "HTTP/1.1 400 Bad Request\r\n";
		break;
	case 403:
		strs << "HTTP/1.1 403 Forbidden\r\n";
		break;
	case 404:
		strs << "HTTP/1.1 404 Not Found\r\n";
		break;
	case 408:
		strs << "HTTP/1.1 408 Request Timeout\r\n";
		break;
	case 500:
		strs << "HTTP/1.1 500 Internal Server Error\r\n";
		break;
	default:
		strs << "HTTP/1.1 " << code << " Unknown Statuscode\r\n";
		break;
	}

	for (auto& i : Headers)
		if (i.Key.length() && i.Value.length())
			strs << i.Key << ": " << i.Value << "\r\n";

	strs << "Content-Length: " << data.size() << "\r\n\r\n";
	auto headers = strs.str();
	send(clientSocket, headers.c_str(), headers.size(), 0);

	if (data.size())
		send(clientSocket, (const char*)&data[0], data.size(), 0);
}

void Response::Write(const std::string& value)
{
	data.resize(data.size() + value.size());
	memcpy(&data[data.size() - value.size()], value.c_str(), value.size());
}

void Response::Write(const char* value)
{
	Write(std::string(value));
}

template<typename T>
inline void Response::Write(const std::vector<T>& values)
{
	data.resize(data.size() + values.size());
	memcpy(&data[data.size() - values.size()], &values[0], values.size());
}

void Response::Write(const Packet& p)
{
	Write(p.Id);
	Write(false);
	Write((int)p.Data.size());
	Write(p.Data);
}

void Response::SetHeader(const std::string& Key, const std::string& Value)
{
	for (auto& i : Headers) {
		if (!i.Key.size()) {
			i = { Key, Value };
			break;
		}
		else if (Header::iequals(i.Key, Key)) {
			i.Value = Value;
			break;
		}
	}
}