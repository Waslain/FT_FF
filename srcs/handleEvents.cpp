#include "Server.hpp"

void	Server::_printMessage(std::string msg, std::string str, int const &fd)
{
	std::stringstream	ss;
	std::string			tmp;
	std::string			space;

	ss << fd;
	ss >> tmp;
	msg += tmp + ": ";
	space.replace(0, msg.size(), msg.size(), ' ');

	std::cout << YELLOW << msg << RESETCOLOR;

	std::string	s;
	size_t		pos = 0;
	int			i = 0;
	while (true)
	{
		pos = str.find("\n");
		if (pos == std::string::npos) {
			break ;
		}
		s = str.substr(0, pos + 1);
		str.erase(0, pos + 1);
		if (i)
			std::cout << space;
		std::cout << s;
		i++;
	}
	if (!str.empty()) {
		std::cout << str << "\n";
	}
	std::cout << std::flush;
}

void	Server::_receiveMessage(int const &fd)
{
	char	buf[1024] = {0};

	if (recv(fd, buf, 1024, 0) < 0) {
		std::cout << "Error: recv: " << strerror(errno) << std::endl;
		return ;
	}
	_printMessage("Received: ", std::string(buf), fd);

	std::string	s = _users[fd].getRecvBuf() + buf;
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
		_parseInput(msg, fd);
	}
	_users[fd].setRecvBuf(s);
}

void	Server::_sendMessage(int &fd)
{
	std::string	msg = _users[fd].getSendBuf();
	char const	*buf = msg.c_str();
	size_t		len = msg.size();

	if (send(fd, buf, len, MSG_NOSIGNAL) < 1) {
		std::cout << "Error: send: " << strerror(errno) << std::endl;
		return ;
	}
	_printMessage("Sent: ", msg, fd);
	_users[fd].setSendBuf("");
}

void	Server::_deleteClient(size_t const &i)
{
	int		fd = _pfds[i].fd;

	std::cout << BBLUE << "Client " << fd << " disconnected" << RESETCOLOR << std::endl;
	shutdown(fd, SHUT_RDWR);
	close(fd);
	std::vector<pollfd>::iterator	it = _pfds.begin();
	_nbUsers--;
	if (_users[fd].getMode('i')) {
		_nbIUsers--;
	}
	if (_users[fd].isRegistered() == false) {
		_nbUConnections--;
	}
	_pfds.erase(it + i);
	_users.erase(fd);
}

void	Server::_acceptClient()
{
	// create a new pollfd node to pass to poll()
	pollfd	pfd;

	// accept the connection, creating a new fd for the client
	pfd.fd = accept(_pfds[0].fd, NULL, NULL);
	if (pfd.fd < 0)
	{
		std::cout << RED << "Error: accept:" << strerror(errno) << RESETCOLOR << std::endl;
		throw emptyException();
	}

	// set the fd as non blocking
	if (fcntl(pfd.fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << RED << "Error: fcntl: " << strerror(errno) << RESETCOLOR << std::endl;
		throw emptyException();
	}

	std::cout << BGREEN << "New client connected, fd = " << pfd.fd << RESETCOLOR << std::endl;

	// set the event checked by poll
	// not sure that i need all of these
	pfd.events = POLLIN | POLLOUT | POLLERR | POLLRDHUP | POLLHUP;
	pfd.revents = 0;
	_pfds.push_back(pfd);

	// create a new user
	_users[pfd.fd] = User(pfd.fd);

	_nbUConnections++;
	_nbUsers++;
	if (_nbUsers > _maxUsers) {
		_maxUsers = _nbUsers;
	}
}
