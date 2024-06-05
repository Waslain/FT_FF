#include "Server.hpp"

void	Server::_sendName(User &user, std::string const &channame)
{
	if (_channels.find(channame) != _channels.end()) {
		_addClientMessage(user, RPL_NAMEREPLY(user, channame));
	}
	_addClientMessage(user, RPL_ENDOFNAMES(user, channame));
}

void	Server::_NAMES(int const &fd, std::string &args)
{
	User		&user = _users[fd];
	std::string	channels = getFirstWord(args);

	std::string	str;
	size_t		pos = 0;

	while (channels.empty() == false)
	{
		pos = channels.find(',');
		str = channels.substr(0, pos);
		channels.erase(0, pos + 1);
		if (pos == std::string::npos) {
			channels.clear();
		}
		_sendName(user, str);
	}
}
