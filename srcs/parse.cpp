#include "Server.hpp"

void Server::_parseInput(std::string &str, int const &fd)
{
	User	&user = _users[fd];

	if (str.size() > INPUTLEN)
	{
		_addClientMessage(user, ERR_INPUTTOOLONG(user));
		return ;
	}
	std::string	cmd = getFirstWord(str);
	if (cmd.empty())
	{
		if (DEBUG == 1)
			std::cerr << "Received empty string" << std::endl;
		return ;
	}
	if (DEBUG) {
		std::cout << "cmd: " << cmd << std::endl;
		std::cout << "args: " << str << std::endl;
	}

	strToupper(cmd);
	if (!_users[fd].isRegistered() && cmd.compare("CAP") && cmd.compare("PASS") && cmd.compare("NICK") && cmd.compare("USER"))
	{
		_addClientMessage(user, ERR_NOTREGISTERED(user));
		return ;
	}
	if (_cmdmap[cmd] != NULL) {
		(*this.*_cmdmap[cmd])(fd, str);
	}
	else {
		_addClientMessage(user, ERR_UNKNOWNCOMMAND(user, cmd));
	}
}
