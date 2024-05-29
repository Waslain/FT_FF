#include "Server.hpp"

static bool is_alnum(char c)
{
    return (isalpha(c) || isdigit(c));
}

static bool is_valid_not_alnum_char(char c)
{
	return (c == '[' || c == ']' || c == '\\' || c == '{' || c == '}' || c == '|');
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
	for (int i = 0; args[i]; i++)
	{
		if (!is_alnum(args[i]))
		{
			if (!is_valid_not_alnum_char(args[i]))
			{
				_addClientMessage(user, ERR_ERRONEUSNICKNAME(user));
				return ;
			}
		}
	}	
	userIt it = this->_users.begin();
	userIt ite = this->_users.end();
	while (it != ite)
	{
		if (it->second.getNickname() == args)
		{
			if (DEBUG)
				std::cout << "Nickname already in use by user " << it->first << std::endl;
			_addClientMessage(user, ERR_NICKNAMEINUSE(user));
			return ;
		}
		it++;
	}
	user.setNickname(args);
}
