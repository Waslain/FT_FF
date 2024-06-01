#include "Server.hpp"

void	Server::_PING(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (DEBUG) {
		std::cout << "Ping cmd received from user[" << fd << "]" << std::endl;
	}
	if (args.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "PING"));
		return ;
	}
	_addClientMessage(user, PONG(args));
}
