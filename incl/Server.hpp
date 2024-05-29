/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:42 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/28 19:21:21 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <sys/signalfd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

#include "User.hpp"
#include "Message.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

extern bool	run;

class User;

class Server
{
	public:
		Server(std::string port, std::string password);
		~Server();
		
		void	loop();
		void 	parseInput(std::string &str, int const &);

	private:
	
		Server();
		Server(const Server &copy);
		Server &operator=(const Server &src);

		typedef std::map<int, User>::iterator	userIt;

		std::string				 _pass;
		std::string				_host;
		int 					_socket;
		std::vector<pollfd>		_pfds;
		std::map<int, User>		_users;
		std::map<std::string, void(Server::*)(int const &, std::string &)> _cmdmap;

		void	_PASS(int const &fd, std::string &args);
		void	_CAP(int const &fd, std::string &args);

		void 	_initCmdMap();
		void	_getSocket(std::string const &);
		void	_checkEvents(size_t const &i);
		void	_acceptClient();
		void	_deleteClient(size_t const &i);
		void	_receiveMessage(int const &fd);
		void	_sendMessage(int &fd);
		void	_addClientMessage(User &user, std::string const &msg);
};

std::string	getFirstWord(std::string &str);
