#include "Server.hpp"

void		Server::_VERSION(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (!args.empty() && args.compare(HOSTNAME))
	{
		_addClientMessage(user, ERR_NOSUCHSERVER(user, args));
		return ;
	}
	_addClientMessage(user, RPL_VERSION(user));
	_addClientMessage(user, RPL_ISUPPORT(user));
}
