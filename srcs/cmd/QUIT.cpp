#include "Server.hpp"

void		Server::_QUIT(int const &fd, std::string &args)
{
	User	&user = this->_users[fd];

	_addClientMessage(user, ERROR("disconnection"));
	user.setDisconnection();
	(void)args;
}
