#include "Server.hpp"

std::string	Server::_getModeString(User &user, std::map<char, bool> const &set)
{
	std::map<char, bool>::const_iterator	it = set.begin();
	std::map<char, bool>::const_iterator	ite = set.end();
	std::string								setTrue = "+";
	std::string								setFalse = "-";

	for (; it != ite; it++)
	{
		if (user.getMode(it->first) == it->second) {
			continue ;
		}
		user.setMode(it->first, it->second);
		if (it->second == false)
		{
			setFalse += it->first;
			continue ;
		}
		setTrue += it->first;
	}
	if (setTrue.size() == 1) {
		setTrue.clear();
	}
	if (setFalse.size() == 1) {
		setFalse.clear();
	}
	return (setFalse + setTrue);
}

int	Server::_setChannelKey(Channel &channel, std::string &params, std::string &args, bool const &value)
{
	if (value == false)
	{
		if (channel.getKey().empty()) {
			return (1);
		}
		channel.setKey(std::string());
	}
	else
	{
		std::string	key = getFirstWord(args);
		if (key.empty()) {
			return (1);
		}
		channel.setKey(key);
		params += std::string(" ") + key;
	}
	return (0);
}

int	Server::_setOperator(Channel &channel, std::string &params, User &user, std::string &args, bool const &value)
{
	std::string	nick = getFirstWord(args);
	if (nick.empty()) {
		return (1);
	}
	User	*target = _getUser(nick);
	if (target == NULL) {
		return (1);
	}
	if (value == false)
	{
		if (channel.isOperator(*target) == false) {
			return (1);
		}
		channel.removeOperator(*target);
		params += std::string(" ") + nick;
	}
	else {
		if (channel.isOperator(*target) == true) {
			return (1);
		}
		if (target->isOnChannel(channel.getName()) == false)
		{
			_addClientMessage(user, ERR_USERNOTINCHANNEL(user, nick, channel.getName()));
			return (1);
		}
		channel.addOperator(*target);
		params += std::string(" ") + nick;
	}
	return (0);
}

int	Server::_setUserLimit(Channel &channel, std::string &params, std::string &args, bool const &value)
{
	if (value == false) {
		if (channel.getUserLimit() == -1) {
			return (1);
		} channel.setUserLimit(-1);
	}
	else
	{
		std::string	limit = getFirstWord(args);
		if (limit.empty()) {
			return (1);
		}
		std::stringstream	ss;
		int					n;
		ss << limit;
		ss >> n;
		if (n == channel.getUserLimit()) {
			return (-1);
		}
		channel.setUserLimit(n);
		params += std::string(" ") + itos(n);
	}
	return (0);
}

std::string	Server::_getModeString(User &user, Channel &channel, std::map<char, bool> const &set, std::string &args)
{
	std::map<char, bool>::const_iterator	it = set.begin();
	std::map<char, bool>::const_iterator	ite = set.end();
	std::string								setTrue = "+";
	std::string								setFalse = "-";
	std::string								params;

	for (; it != ite; it++)
	{
		char	c = it->first;
		switch (c)
		{
			case 'i':
			case 't':
				if (channel.getMode(c) == it->second) {
					continue ;
				}
				channel.setMode(c, it->second);
				break ;
			case 'k':
				if (_setChannelKey(channel, params, args, it->second)) {
					continue ;
				}
				break ;
			case 'o':
				if (_setOperator(channel, params, user, args, it->second)) {
					continue ;
				}
				break ;
			case 'l':
				if (_setUserLimit(channel, params, args, it->second)) {
					continue ;
				}
				break ;
		}
		if (it->second == true) {
			setTrue += c;
		}
		else {
			setFalse += c;
		}
	}
	if (setTrue.size() == 1) {
		setTrue.clear();
	}
	if (setFalse.size() == 1) {
		setFalse.clear();
	}
	return (setFalse + setTrue);
}

std::map<char, bool>	Server::_parseModeString(std::string &args, bool &unknown, std::string const &modes)
{
	std::string				str = getFirstWord(args);
	int						sign = -1;
	std::map<char, bool>	set;
	std::string				alreadySet;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '+')
		{
			sign = 1;
			continue ;
		}
		if (str[i] == '-')
		{
			sign = 0;
			continue ;
		}
		if (sign == -1) {
			continue ;
		}
		if (modes.find(str[i]) == std::string::npos)
		{
			unknown = true;
			continue ;
		}
		if (alreadySet.find(str[i]) != std::string::npos) {
			continue ;
		}
		bool	value = static_cast<bool>(sign);
		std::map<char, bool>::iterator	it = set.find(str[i]);
		if (it != set.end() && it->second != value)
		{
			set.erase(str[i]);
			alreadySet += str[i];
			continue ;
		}
		set[str[i]] = value;
	}
	return (set);
}

void	Server::_channelModes(User &user, std::string const &target, std::string &args)
{
	chanIt	it = _channels.find(target);
	if (it == _channels.end())
	{
		_addClientMessage(user, ERR_NOSUCHCHANNEL(user, target));
		return ;
	}

	if (args.empty())
	{
		_addClientMessage(user, RPL_CHANNELMODEIS(user, target));
		return ;
	}

	if (user.isOperator(target) == false)
	{
		_addClientMessage(user, ERR_CHANOPRIVSNEEDED(user, target));
		return ;
	}

	bool					unknown = false;
	std::map<char, bool>	set = _parseModeString(args, unknown, "itkol");

	_addChannelMessage(user, it->second, MODE(user, target, _getModeString(user, _channels[target], set, args)), ALL);
	if (unknown) {
		_addClientMessage(user, ERR_UMODEUNKNOWNFLAG(user));
	}
}

void	Server::_userModes(User &user, std::string const &target, std::string &args)
{
	if (_isNickOnServer(target) == false)
	{
		_addClientMessage(user, ERR_NOSUCHNICK(user, target));
		return ;
	}

	if (user.getNickname().compare(target))
	{
		_addClientMessage(user, ERR_USERDONTMATCH(user));
		return ;
	}

	if (args.empty())
	{
		_addClientMessage(user, RPL_UMODEIS(user));
		return ;
	}

	bool					unknown = false;
	std::map<char, bool>	set = _parseModeString(args, unknown, USERMODES);

	_addClientMessage(user, MODE(user, target, _getModeString(user, set)));
	if (unknown) {
		_addClientMessage(user, ERR_UMODEUNKNOWNFLAG(user));
	}
}

void	Server::_MODE(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	std::string	target = getFirstWord(args);
	if (target.empty() || target[0] != '#') {
		_userModes(user, target, args);
	}
	else {
		_channelModes(user, target, args);
	}
}
