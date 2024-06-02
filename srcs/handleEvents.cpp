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
	char	buf[INPUTLEN] = {0};

	if (recv(fd, buf, INPUTLEN, MSG_DONTWAIT) < 0)
	{
		if (errno != EAGAIN || errno != EWOULDBLOCK) {
			std::cout << RED <<  "Error: recv: " << strerror(errno) << RESETCOLOR << std::endl;
		}
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
	User		&user = _users[fd];
	std::string	msg = user.getSendBuf();
	std::string	msgSent;
	char const	*buf = msg.c_str();
	size_t		len = msg.size();
	size_t		sent = 0;

	sent = send(fd, buf, len, MSG_NOSIGNAL|MSG_DONTWAIT);
	if (sent < 1)
	{
		if (errno != EAGAIN || errno != EWOULDBLOCK) {
			std::cout << RED << "Error: send: " << strerror(errno) << RESETCOLOR<< std::endl;
		}
		return ;
	}
	msgSent = msg.substr(0, sent);
	msg.erase(0, sent);
	_printMessage("Sent: ", msgSent, fd);
	user.setSendBuf(msg);
	if (user.canRegister() & msg.empty())
	{
		user.setRegistration(false);
		user.registerUser();
	}
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
	_users[fd].clearChannels("user disconnected");
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
	_nbIUsers++;
	if (_nbUsers > _maxUsers) {
		_maxUsers = _nbUsers;
	}
}
