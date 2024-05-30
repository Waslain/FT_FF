#include "Server.hpp"

void		Server::_QUIT(int const &fd, std::string &args)
{
	User	&user = this->_users[fd];

	user.setDisconnection();
	_addClientMessage(user, ERROR("disconnection"));
	(void)args;
}
