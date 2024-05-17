/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/16 19:26:48 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_getSocket()
{
	int				status;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = getprotobyname("TCP")->p_proto;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, this->_port.c_str(), &hints, &res);
	if (status != 0)
	{
		std::cerr << gai_strerror(status) << std::endl;
		throw (emptyException());
	}

	for (p = res; p != NULL; p = p->ai_next)
	{
		this->_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (this->_socket < 0)
		{
			std::cerr << "socket error" << std::endl;
			continue ;
		}
		if (bind(this->_socket, p->ai_addr, p->ai_addrlen) < 0)
		{
			std::cerr << "bind error" << std::endl;
			close(this->_socket);
			continue ;
		}

		break ;
	}

		char	ipstr[INET6_ADDRSTRLEN];
		inet_ntop(p->ai_family, p->ai_addr, ipstr, sizeof (ipstr));
		std::cout << ipstr << std::endl;

	if (p == NULL)
	{
		std::cerr << strerror(errno) << std::endl;
		throw (emptyException());
	}

	freeaddrinfo(res);
}

Server::Server(std::string port, std::string password): _pass(password)
{
	this->_port = port;
	_getSocket();
}

Server::~Server()
{
	close(this->_socket);
}

// this code may be temporary
void	Server::loop()
{
	listen(this->_socket, 5);

	int	clientSocket = accept(this->_socket, NULL, NULL);

	char	buffer[1024] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);
	std::cout << "Message: " << buffer << std::endl;
}
