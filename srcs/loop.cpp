#include "Server.hpp"

void	Server::_receiveMessage(int const &fd)
{
	char	buf[1024] = {0};

	if (recv(fd, buf, 1024, 0) < 0) {
		std::cout << "Error: recv: " << strerror(errno) << std::endl;
		return ;
	}

	std::string	s = this->_users[fd].getRecvBuf() + buf;
	std::string	msg;
	size_t		pos = 0;

	while (true)
	{
		pos = s.find("\r\n");
		if (pos == std::string::npos) {
			break ;
		}
		msg = s.substr(0, pos);
		s.erase(0, pos + 2);
		parseInput(msg, fd);
	}
	this->_users[fd].setRecvBuf(s);
}

void	Server::_sendMessage(int &fd)
{
	std::string	msg = this->_users[fd].getSendBuf();
	char const	*buf = msg.c_str();
	size_t		len = msg.size();

	if (send(fd, buf, len, 0) < 1) {
		std::cout << "Error: send: " << strerror(errno) << std::endl;
		return ;
	}
	std::cout << "sent: " << msg << std::flush;
	this->_users[fd].setSendBuf("");
}

void	Server::_deleteClient(size_t const &i)
{
	int		fd = this->_pfds[i].fd;

	std::cout << "Client " << fd << " disconnected" << std::endl;
	shutdown(fd, SHUT_RDWR);
	close(fd);
	std::vector<pollfd>::iterator	it = this->_pfds.begin();
	this->_pfds.erase(it + i);
	this->_users.erase(this->_users.find(fd));
}

void	Server::_acceptClient()
{
	// create a new pollfd node to pass to poll()
	pollfd	pfd;

	// accept the connection, creating a new fd for the client
	pfd.fd = accept(this->_pfds[0].fd, NULL, NULL);
	if (pfd.fd < 0)
	{
		std::cout << "Error: accept:" << strerror(errno) << std::endl;
		throw ;
	}

	// set the fd as non blocking
	if (fcntl(pfd.fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "Error: fcntl: " << strerror(errno) << std::endl;
		throw ;
	}

	std::cout << "New client connected, fd = " << pfd.fd << std::endl;

	// set the event checked by poll
	// not sure that i need all of these
	pfd.events = POLLIN | POLLOUT | POLLERR | POLLRDHUP | POLLHUP;
	pfd.revents = 0;
	this->_pfds.push_back(pfd);

	// create a new user
	this->_users[pfd.fd] = User();
}

void	Server::_checkEvents(size_t const &i)
{
	int		&fd = this->_pfds[i].fd;
	User	&user = this->_users[fd];

	// when client sends
	if (this->_pfds[i].revents & POLLIN) {
		_receiveMessage(fd);
	}

	// if the client is not registered, check if registration is possible
	if (user.isRegistered() == false) {
		_checkRegistration(fd);
	}

	// when client is ready to receive
	if (this->_pfds[i].revents & POLLOUT && !user.getSendBuf().empty()) {
		_sendMessage(fd);
	}

	// not sure about this one
	if (this->_pfds[i].revents & POLLERR) {
		std::cout << "Client " << fd << " POLLERR" << std::endl;
	}

	// if the client is closed -> close his fd and remove it from pfds
	if (this->_pfds[i].revents & POLLRDHUP || user.disconnect()) {
		_deleteClient(i);
	}
}

void	Server::loop()
{
	while (run)
	{
		// poll will wait for any file file descriptor ready to perform I/O 
		poll(&this->_pfds[0], this->_pfds.size(), 1000);

		for (size_t i = 1; i < this->_pfds.size(); i++) {
			_checkEvents(i);
		}
		
		// if the socket is ready for an input event -> a client is trying to connect
		if (this->_pfds[0].revents & POLLIN) {
			_acceptClient();
		}
	}
}
