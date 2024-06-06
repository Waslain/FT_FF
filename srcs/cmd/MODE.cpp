#include "Server.hpp"

void	Server::_channelModes(User &user, std::string const &target, std::string &args)
{
	(void)user;
	(void)target;
	(void)args;
}

std::string	getModeString(User &user, std::map<char, bool> const &set)
{
	std::map<char, bool>::const_iterator	it = set.begin();
	std::map<char, bool>::const_iterator	ite = set.end();
	std::string								setTrue = "+";
	std::string								setFalse = "-";

	for (; it != ite; it++)
	{
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

	std::string				str = getFirstWord(args);
	std::string				usermodes = USERMODES;
	int						sign = -1;
	bool					unknown = false;
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
		if (usermodes.find(str[i]) == std::string::npos)
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

	_addClientMessage(user, MODE(user, target, getModeString(user, set)));
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
