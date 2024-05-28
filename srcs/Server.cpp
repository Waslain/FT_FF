/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/28 15:09:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void PrintTestFunction()
{
	std::cout << "Test function called" << std::endl;
}

void Server::_initCmdMap()
{
	// std::string cmd = "TEST";
	// _cmdmap[cmd] = &PrintTestFunction;
	_cmdmap["TEST"] = &PrintTestFunction;
}

void Server::parseInput(std::string str)
{
	std::cout << "Received: " << str << std::endl;
	if (_cmdmap[str] != NULL)
		_cmdmap[str]();
}

Server::Server(std::string port, std::string password): _pass(password)
{
	_initCmdMap();
	_getSocket(port);
}

Server::~Server()
{
	close(this->_socket);
	std::vector<pollfd>::iterator	it = this->_pfds.begin();
	std::vector<pollfd>::iterator	ite = this->_pfds.end();
	for (; it < ite; it++) {
		close(it->fd);
	}
}
