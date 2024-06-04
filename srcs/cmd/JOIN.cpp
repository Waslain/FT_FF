#include "Server.hpp"

bool		isChannelNameValid(std::string &channel)
{
	std::string	set = "\a,";
	if (channel.size() > CHANNELLEN || channel.size() <= 1) {
		return (false);
	}
	if (channel.empty() || channel[0] != '#') {
		return (false);
	}
	if (channel.find_first_of(set, 0) != std::string::npos) {
		return (false);
	}
	return (true);
}

void		Server::_joinChannel(User &user, std::string &channel, std::string &key)
{
	if (!isChannelNameValid(channel)) {
		_addClientMessage(user, ERR_BADCHANMASK(user));
		return ;
	}

	// if user is already on channel -> don't know what reply is needed here
	if (user.isOnChannel(channel)) {
		return ;
	}

	if (user.getNbChannels() == CHANLIMIT) {
		_addClientMessage(user, ERR_TOOMANYCHANNELS(user, channel));
		return ;
	}
	
	// if channel doesn't exist, create it, else check if we can join it
	if (_channels.find(channel) == _channels.end()) {
		_channels[channel] = Channel(user, channel);
		user.joinChannel(_channels[channel]);
		_nbChannels++;
	}
	else
	{
		std::string chanKey = _channels[channel].getKey();
		if (!chanKey.empty() && chanKey.compare(key))
		{
			_addClientMessage(user, ERR_BADCHANNELKEY(user, channel));
			return ;
		}
		if (_channels[channel].getMode('i'))
		{
			_addClientMessage(user, ERR_INVITEONLYCHAN(user, channel));
			return ;
		}
		if (_channels[channel].getNbUsers() == _channels[channel].getUserLimit())
		{
			_addClientMessage(user, ERR_CHANNELISFULL(user, channel));
			return ;
		}
		_channels[channel].addUser(user);
		user.joinChannel(_channels[channel]);
	}

	// send the replies
	_addChannelMessage(_channels[channel], JOIN(user, channel));
	if (!_channels[channel].getTopic().empty())
	{
		_addClientMessage(user, RPL_TOPIC(user, _channels[channel]));
		_addClientMessage(user, RPL_TOPIC(user, _channels[channel]));
	}
	// RPL_NAMEREPLY and RPL_ENDOFNAMES not yet implemented
}

void		Server::_JOIN(int const &fd, std::string &args)
{
	User		&user = _users[fd];
	std::string	channels = getFirstWord(args);
	std::string	keys = getFirstWord(args);

	if (channels.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "JOIN "));
		return ;
	}

	if (!channels.compare("0"))
	{
		user.clearChannels("");
		return ;
	}

	std::string	channel;
	std::string	key;
	size_t	pos = 0;

	while (!channels.empty())
	{
		pos = channels.find(',');
		channel = channels.substr(0, pos);
		channels.erase(0, pos + 1);
		if (pos == std::string::npos) {
			channels.clear();
		}
		pos = keys.find(',');
		key = keys.substr(0, pos);
		keys.erase(0, pos + 1);
		if (pos == std::string::npos) {
			keys.clear();
		}
		if (channel.empty()) {
			continue ;
		}
		_joinChannel(user, channel, key);
	}
}
