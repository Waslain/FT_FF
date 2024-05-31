/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:42 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/30 16:19:42 by fduzant          ###   ########.fr       */
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
#include <time.h>

#include "colors.hpp"
#include "User.hpp"
#include "Channel.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

#define TIMEOUT 20
#define VERSION "ft_ff-1.0"
#define HOSTNAME "ft_ff"
#define USERLEN 20
#define	USERMODES "i"
#define	CHANMODES "iklot"

extern bool	run;

class User;
class Channel;

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

		std::string				 		_pass;
		std::string						_host;
		int 							_socket;
		time_t							_time;
		std::vector<pollfd>				_pfds;
		std::map<int, User>				_users;
		std::map<std::string, void(Server::*)(int const &, std::string &)> _cmdmap;

		void		_CAP(int const &fd, std::string &args);
		void		_PASS(int const &fd, std::string &args);
		void		_NICK(int const &fd, std::string &args);
		void		_USER(int const &fd, std::string &args);
		void		_PING(int const &fd, std::string &args);
		void		_QUIT(int const &fd, std::string &args);

		//UTILS
		bool		nick_already_in_use(std::string nick);
		//UTILS

		void 		_initCmdMap();
		void		_getSocket(std::string const &);
		void		_checkEvents(size_t const &i);
		void		_acceptClient();
		void		_deleteClient(size_t const &i);
		void		_receiveMessage(int const &fd);
		void		_sendMessage(int &fd);
		void		_printMessage(std::string msg, std::string str, int const &fd);
		void		_addClientMessage(User &user, std::string const &msg);
		void		_checkRegistration(int &fd);
		void		_registerClient(User &user);

		// messages
		std::string	RPL_WELCOME(User &user);
		std::string	RPL_YOURHOST(User &user);
		std::string	RPL_CREATED(User &user);
		std::string	RPL_MYINFO(User &user);
		std::string	RPL_ISUPPORT(User &user);
		std::string ERR_NONICKNAMEGIVEN(User &user);
		std::string ERR_ERRONEUSNICKNAME(User &user);
		std::string ERR_NICKNAMEINUSE(User &user);
		std::string ERR_NEEDMOREPARAMS(User &user, std::string command);
		std::string ERR_ALREADYREGISTERED(User &user);
		std::string ERR_PASSWDMISMATCH(User &user);
		std::string ERROR(std::string msg);
		std::string	PONG(std::string &token);
		std::string	_numeric(User &, std::string, std::string &, std::string);
		std::string	_getDate();
};

class	emptyException: public std::exception
{
	virtual const char	*what() const throw()
	{
		return (NULL);
	}

};

std::string	getFirstWord(std::string &str);
