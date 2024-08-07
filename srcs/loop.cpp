#include "Server.hpp"

void	Server::_checkEvents(size_t const &i)
{
	int		&fd = _pfds[i].fd;
	User	&user = _users[fd];

	// when client sends
	if (_pfds[i].revents & POLLIN) {
		_receiveMessage(fd);
	}

	// if the client is not registered, check if registration is possible
	if (user.isRegistered() == false) {
		_checkRegistration(fd);
	}

	// when client is ready to receive
	if (_pfds[i].revents & POLLOUT && !user.getSendBuf().empty()) {
		_sendMessage(fd);
	}

	// not sure about this one
	if (_pfds[i].revents & POLLERR) {
		std::cout << "Client " << fd << " POLLERR" << std::endl;
	}

	// if the client is closed -> close his fd and remove it from pfds
	if (_pfds[i].revents & POLLRDHUP || user.disconnect()) {
		if (_users[fd].getReason().empty()) {
			_users[fd].setReason("client disconnected");
		}
		_deleteClient(i);
	}
}

void	Server::loop()
{
	while (run)
	{
		// poll will wait for any file file descriptor ready to perform I/O 
		poll(&_pfds[0], _pfds.size(), 1000);

		for (size_t i = 1; i < _pfds.size(); i++) {
			_checkEvents(i);
		}
		
		// if the socket is ready for an input event -> a client is trying to connect
		if (_pfds[0].revents & POLLIN) {
			_acceptClient();
		}
	}

	_users.clear();
	_channels.clear();

}
