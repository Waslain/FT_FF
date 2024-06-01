#include "Server.hpp"

void	Server::_USER(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (user.canRegister()) {
		return ;
	}
	if (user.isRegistered()) {
		_addClientMessage(user, ERR_ALREADYREGISTERED(user));
		return ;
	}

	std::string	username = getFirstWord(args);
	std::string	tmp = getFirstWord(args);
	tmp = getFirstWord(args);
	std::string	realname = args;

	if (username.empty() || realname.empty()) {
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "USER"));
		return ;
	}

	// format the username -> if it is longer than USERLEN, truncate it
	username = "~" + username;
	username = username.substr(0, USERLEN);

	user.setUsername(username);
	user.setRealname(realname);
}
