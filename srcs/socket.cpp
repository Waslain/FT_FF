#include "Server.hpp"

void	Server::_getSocket(std::string const &port)
{
	int				status;
	struct addrinfo	hints;
	struct addrinfo	*res;

	// specify the parameters of the internet address we want to get
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;						// specify the type of address -> unspec means both ipv4 and ipv6 work
	hints.ai_socktype = SOCK_STREAM;					// specify the type of socket -> stream socket
	hints.ai_protocol = getprotobyname("TCP")->p_proto;	// specify the protocol we want to use -> TCP
	hints.ai_flags = AI_PASSIVE;						// flags -> AI_PASSIVE means we want any local address

	// get a list of internet addresses using the right port and following the parameters in hints
	status = getaddrinfo(NULL, port.c_str(), &hints, &res);
	if (status != 0)
	{
		std::cerr << RED << gai_strerror(status) << RESETCOLOR << std::endl;
		throw emptyException();
	}

	// iterate through the list of addresses
	struct addrinfo *p;
	for (p = res; p != NULL; p = p->ai_next)
	{
		// get ad fd to a socket
		_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (_socket < 0) {
			continue ;
		}

		// allow the socket to be reused quickly after closing it
		int	yes = 1;
		setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

		// bind the socket to the address
		if (bind(_socket, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(_socket);
			continue ;
		}
		break ;
	}

	if (p == NULL)
	{
		std::cerr << RED << "Error: " << strerror(errno) << RESETCOLOR << std::endl;
		throw emptyException();
	}

	// print the address
	/*
	char	ipstr[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, p->ai_addr, ipstr, sizeof (ipstr));
	std::cout << ipstr << std::endl;
	*/

	// free the addrinfo list
	freeaddrinfo(res);

	// mark the socket as a passive socket, used to accept connection requests
	if (listen(_socket, 10) < 0)
	{
		std::cerr << RED<< "Error: " << strerror(errno) << RESETCOLOR << std::endl;
		throw emptyException();
	}

	// set the socket as non blocking
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << RED << "Error: " << strerror(errno) << RESETCOLOR << std::endl;
		throw emptyException();
	}

	pollfd	pfd;
	pfd.fd = _socket;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pfds.push_back(pfd);
}
