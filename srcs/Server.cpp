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

Server::Server(int port, std::string password)
{
	// create a stream socket
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0) {
		throw (Server::errnoException());
	}

	// create an address
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
	if (inet_pton(AF_INET, "127.0.0.0",  &(this->_address.sin_addr)) < 0) {
		throw (Server::errnoException());
	}

	for (size_t i = 0; i < 8; i++) {
		this->_address.sin_zero[i] = 0;
	}
	
	// code to print the ip address
	char	ip4[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(this->_address.sin_addr), ip4, INET_ADDRSTRLEN);
	std::cout << ip4 << std::endl;

	// bind address to the socket
	bind(this->_socket, reinterpret_cast<struct sockaddr*>(&this->_address), sizeof(this->_address));

	this->_pass = password;
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
