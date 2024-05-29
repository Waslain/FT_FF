#include "Server.hpp"

std::string	joinArgs(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end)
{
	std::string	str = "";

	if (it == end) {
		return (str);
	}

	while (true)
	{
		str += *it;
		if (it + 1 == end) {
			break ;
		}
		str += " ";
		it++;
	}
	return (str);
}

void	Server::_PASS(int const &fd, std::vector<std::string> &args)
{
	User	&user = this->_users[fd];

	std::string	pass = joinArgs(args.begin(), args.end());
	if (DEBUG) {
		std::cout << "password received: " << pass << std::endl;
	}
	if (user.isRegistered())
	{
		_addClientMessage(user, ERR_ALREADYREGISTERED(user));
		return ;
	}
	if (pass.empty())
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "PASS"));
		return ;
	}
	if (pass != this->_pass)
	{
		_addClientMessage(user, ERR_PASSWDMISMATCH(user));
		return ;
	}
	user.setPassword(pass);
}
