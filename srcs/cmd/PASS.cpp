#include "Server.hpp"

void	Server::_PASS(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (DEBUG) {
		std::cout << "password received: " << args << std::endl;
	}
	if (user.canRegister()) {
		return ;
	}
	if (user.isRegistered())
	{
		_addClientMessage(user, ERR_ALREADYREGISTERED(user));
		return ;
	}
	if (args.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "PASS "));
		return ;
	}
	user.setPassword(args);
}
