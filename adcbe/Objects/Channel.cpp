#include "Channel.h"

Channel::Channel(const std::string& name, const std::string& topic)
{
	Name = name;
	Topic = topic;
	Players.reserve(16);
}
