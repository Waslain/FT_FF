#include "Server.hpp"

static bool is_alnum(char c)
{
    return (isalpha(c) || isdigit(c));
}

static bool is_valid_not_alnum_char(char c)
{
	return (c == '[' || c == ']' || c == '\\' || c == '{' || c == '}' || c == '|');
}

static bool is_valid_nick(std::string nick)
{
	for (int i = 0; nick[i]; i++)
	{
		if (!is_alnum(nick[i]))
		{
			if (!is_valid_not_alnum_char(nick[i]))
			{
				return false;
			}
		}
	}

	return true;
}

bool	Server::nick_already_in_use(std::string nick)
{
	for (userIt it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getNickname() == nick)
		{
			if (DEBUG)
				std::cout << "Nickname already in use by user " << it->first << std::endl;
			return false;
		}
	}
	return true;
}

void	Server::_NICK(int const &fd, std::string &args)
{
	User	&user = this->_users[fd];

	if (DEBUG) {
		std::cout << "nick received: " << args << std::endl;
	}
	if (args.empty())
	{
		_addClientMessage(user, ERR_NONICKNAMEGIVEN(user));
		return ;
	}
	//Check if args is alphanum
	if (!is_valid_nick(args))
	{
		_addClientMessage(user, ERR_ERRONEUSNICKNAME(user));
		return ;
	}
	//Check if nickname is already in use
	if (!nick_already_in_use(args))
	{
		_addClientMessage(user, ERR_NICKNAMEINUSE(user));
		return ;
	}
	user.setNickname(args);
}
