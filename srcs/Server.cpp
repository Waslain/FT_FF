/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/28 19:57:57 by fduzant          ###   ########.fr       */
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

template <typename T>
static void PrintVectArgs(std::vector<T> args)
{
	for (long unsigned int i = 0; i < args.size(); i++)
		std::cout << "Arg " << i << ": " << args[i] << std::endl;
}

void Server::parseInput(std::string str)
{
	if (str.empty())
	{
		if (DEBUG == 1)
			std::cerr << "Received empty string" << std::endl;
		return ;
	}
	std::cout << "Received: " << str << std::endl;
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	
	std::string s;
	std::stringstream ss(str);
	std::vector<std::string> args;
	while (getline(ss, s, ' '))
	{
		args.push_back(s);
	}
	//print args if DEBUG
	if (DEBUG == 1)
		PrintVectArgs(args);
	if (_cmdmap[args[0]] != NULL)
		_cmdmap[args[0]]();
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
