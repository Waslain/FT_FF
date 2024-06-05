#include "Server.hpp"

void	Server::_TOPIC(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	std::string	channame = getFirstWord(args);
	if (channame.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "TOPIC "));
		return ;
	}

	chanIt	it= _channels.find(channame);
	if (it == _channels.end())
	{
		_addClientMessage(user, ERR_NOSUCHCHANNEL(user, channame));
		return ;
	}

	Channel	&channel = it->second;
	if (user.isOnChannel(channame) == false)
	{
		_addClientMessage(user, ERR_NOTONCHANNEL(user, channame));
		return ;
	}

	std::string	topic = args;
	if (topic.empty())
	{
		topic = channel.getTopic();
		if (topic.empty()) {
			_addClientMessage(user, RPL_NOTOPIC(user, channel));
			return ;
		}
		_addClientMessage(user, RPL_TOPIC(user, channel));
		_addClientMessage(user, RPL_TOPICWHOTIME(user, channel));
		return ;
	}

	if (channel.getMode('t') == true && user.isOperator(channame) == false)
	{
		_addClientMessage(user, ERR_CHANOPRIVSNEEDED(user, channame));
		return ;
	}

	channel.setTopic(user, topic);
	_addChannelMessage(user, channel, RPL_TOPIC(user, channel), ALL);
}
