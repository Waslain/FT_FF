#include "Server.hpp"

void		Server::_QUIT(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	_addClientMessage(user, ERROR("disconnection"));
	user.setDisconnection();
	user.setReason(std::string("Quit: ") + args);
	(void)args;
}
