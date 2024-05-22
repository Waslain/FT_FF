#include "Server.hpp"

void	Server::_checkEvents(size_t const &i)
{
	// when client sends
	if (this->_pfds[i].revents & POLLIN)
	{
	}

	// when client is ready to receive
	if (this->_pfds[i].revents & POLLOUT)
	{
	}

	// not sure about this one
	if (this->_pfds[i].revents & POLLERR)
	{
	}

	// if the client is closed -> close his fd and remove it from pfds
	if (this->_pfds[i].revents & POLLRDHUP)
	{
		std::cout << "Client " << this->_pfds[i].fd << " disconnected" << std::endl;
		close(this->_pfds[i].fd);
		std::vector<pollfd>::iterator	it = this->_pfds.begin();
		this->_pfds.erase(it + i);
	}
}

void	Server::_acceptClient()
{
	// create a new pollfd node to pass to poll()
	pollfd	pfd;

	// accept the connection, creating a new fd for the client
	pfd.fd = accept(this->_pfds[0].fd, NULL, NULL);
	if (pfd.fd < 0)
	{
		std::cout << "Error: " << strerror(errno) << std::endl;
		throw (emptyException());
	}

	std::cout << "New client connected, fd = " << pfd.fd << std::endl;

	// set the event checked by poll
	// not sure that i need all of these
	pfd.events = POLLIN | POLLOUT | POLLERR | POLLRDHUP | POLLHUP;
	this->_pfds.push_back(pfd);
}

void	Server::loop()
{
	while (true)
	{
		// poll will wait for any file file descriptor ready to perform I/O 
		poll(&this->_pfds[0], this->_pfds.size(), -1);

		// to close the program if ctrl-c was used
		if (run == false) {
			return ;
		}

		for (size_t i = 1; i < this->_pfds.size(); i++) {
			Server::_checkEvents(i);
		}
		
		// if the socket is ready for an input event -> a client is trying to connect
		if (this->_pfds[0].revents & POLLIN) {
			Server::_acceptClient();
		}
	}
}
