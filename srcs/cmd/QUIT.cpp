#include "Server.hpp"

void		Server::_QUIT(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	_addClientMessage(user, ERROR("disconnection"));
	user.setDisconnection();
	(void)args;
}
