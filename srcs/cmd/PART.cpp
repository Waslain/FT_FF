#include "Server.hpp"

void	Server::_quitChannel(User &user, std::string const &channame, std::string const &reason)
{
	if (_channels.find(channame) == _channels.end())
	{
		_addClientMessage(user, ERR_NOSUCHCHANNEL(user, channame));
		return ;
	}

	if (!user.isOnChannel(channame))
	{
		_addClientMessage(user, ERR_NOTONCHANNEL(user, channame));
		return ;
	}

	Channel	&channel = _channels[channame];

	_addChannelMessage(channel, PART(user, channame, reason));
	user.leaveChannel(channel);
	channel.removeUser(user);
	if (channel.getNbUsers() == 0)
	{
		_nbChannels--;
		_channels.erase(channame);
		return ;
	}
}

void	Server::_PART(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	std::string	channels = getFirstWord(args);
	std::string	reason = args;
	std::string	channel;
	size_t		pos = 0;

	if (channels.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "PART "));
		return ;
	}

	while (!channels.empty())
	{
		pos = channels.find(',');
		channel = channels.substr(0, pos);
		channels.erase(0, pos + 1);
		if (pos == std::string::npos) {
			channels.clear();
		}
		_quitChannel(user, channel, reason);
	}
}
