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
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);

	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
	this->_address.sin_addr.s_addr = INADDR_ANY;
	
	bind(this->_socket, (struct sockaddr*)&this->_address, sizeof(this->_address));

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
