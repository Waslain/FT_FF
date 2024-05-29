#include "Server.hpp"

void	Server::_PASS(int const &fd, std::string &args)
{
	User	&user = this->_users[fd];

	if (DEBUG) {
		std::cout << "password received: " << args << std::endl;
	}
	if (user.isRegistered())
	{
		_addClientMessage(user, ERR_ALREADYREGISTERED(user));
		return ;
	}
	if (args.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "PASS"));
		return ;
	}
	if (args != this->_pass)
	{
		_addClientMessage(user, ERR_PASSWDMISMATCH(user));
		return ;
	}
	user.setPassword(args);
}
