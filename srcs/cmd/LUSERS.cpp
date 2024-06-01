#include "Server.hpp"

void	Server::_LUSERS(int const &fd, std::string &args)
{
	User	&user = _users[fd];
	static_cast<void>(args);

	_addClientMessage(user, RPL_LUSERCLIENT(user));
	_addClientMessage(user, RPL_LUSEROP(user));
	_addClientMessage(user, RPL_LUSERUNKNOWN(user));
	_addClientMessage(user, RPL_LUSERCHANNELS(user));
	_addClientMessage(user, RPL_LUSERME(user));
	_addClientMessage(user, RPL_LOCALUSERS(user));
	_addClientMessage(user, RPL_GLOBALUSERS(user));
}
