#include "Server.hpp"

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
	User	&user = _users[fd];

	if (DEBUG) {
		std::cout << "nick received: " << args << std::endl;
	}
	if (user.canRegister()) {
		return ;
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
