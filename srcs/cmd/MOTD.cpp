#include "Server.hpp"

void	Server::_MOTD(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (!args.empty() && args.compare(HOSTNAME)) {
		_addClientMessage(user, ERR_NOSUCHSERVER(user));
	}

	std::ifstream	file;
	file.open(MOTD, std::ios::in);
	if (!file.is_open())
	{
		_addClientMessage(user, ERR_NOMOTD(user));
		return ;
	}

	_addClientMessage(user, RPL_MOTDSTART(user));

	std::string	buf;
	while (std::getline(file, buf)) {
		_addClientMessage(user, RPL_MOTD(user, buf));
	}
	file.close();

	_addClientMessage(user, RPL_ENDOFMOTD(user));
}
