#include "Server.hpp"

void	Server::_registerClient(User &user)
{
	// check if the password is correct
	if (user.getPassword() != this->_pass)
	{
		_addClientMessage(user, ERR_PASSWDMISMATCH(user));
		user.setDisconnection();
		return ;
	}
	// register the user
	user.registerUser();
	_addClientMessage(user, RPL_WELCOME(user));
	_addClientMessage(user, RPL_YOURHOST(user));
	_addClientMessage(user, RPL_CREATED(user, _getTime()));
	_addClientMessage(user, RPL_MYINFO(user));
	_addClientMessage(user, RPL_ISUPPORT(user));
}

void	Server::_checkRegistration(int &fd)
{
	User	&user = this->_users[fd];

	// if the client takes too long to send, disconnect it
	if (time(NULL) > user.getTime() + TIMEOUT)
	{
		_addClientMessage(user, ERROR("Connection timeout"));
		user.setDisconnection();
		return ;
	}
	// if all the username or the nickname is not set, return
	if (user.getNickname().empty() || user.getUsername().empty()) {
		return ;
	}

	// go through with the registration process
	_registerClient(user);
}
