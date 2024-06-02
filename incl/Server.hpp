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
#include <fstream>
#include <time.h>

#include "colors.hpp"
#include "User.hpp"
#include "Channel.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

#define TIMEOUT 10
#define VERSION std::string("ircserv-1.42.0")
#define HOSTNAME std::string("ft_irc")
#define MOTD "motd"
#define INPUTLEN 512

#define AWAYLEN 350
#define CHANLIMIT 5
#define	CHANMODES std::string("iklot")
#define CHANNELLEN 50
#define HOSTLEN 50
#define KICKLEN 350
#define NICKLEN 30
#define TOPICLEN 350
#define USERLEN 20
#define	USERMODES std::string("i")

#define	ALPHA std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
#define NUM std::string("0123456789")
#define SPECIAL std::string("[]\\`_^{}|")

extern bool	run;

class User;
class Channel;

class Server
{
	public:
		Server(std::string port, std::string password);
		~Server();
		
		void	loop();

	private:
	
		Server();
		Server(const Server &copy);
		Server &operator=(const Server &src);

		typedef std::map<int, User>::iterator	userIt;

		std::string				 		_pass;
		std::string						_host;
		int 							_socket;
		int								_nbUsers;
		int								_nbIUsers;
		int								_maxUsers;
		int								_nbOperators;
		int								_nbUConnections;
		int								_nbChannels;
		time_t							_time;
		std::vector<pollfd>				_pfds;
		std::map<int, User>				_users;
		std::map<std::string, Channel>	_channels;
		std::map<std::string, void(Server::*)(int const &, std::string &)> _cmdmap;

		void		_CAP(int const &fd, std::string &args);
		void		_PASS(int const &fd, std::string &args);
		void		_NICK(int const &fd, std::string &args);
		void		_USER(int const &fd, std::string &args);
		void		_PING(int const &fd, std::string &args);
		void		_QUIT(int const &fd, std::string &args);
		void		_LUSERS(int const &fd, std::string &args);
		void		_VERSION(int const &fd, std::string &args);
		void		_MOTD(int const &fd, std::string &args);
		void		_JOIN(int const &fd, std::string &args);

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
		void 		_parseInput(std::string &str, int const &);
		void		_addClientMessage(User &user, std::string const &msg);
		void		_checkRegistration(int &fd);
		void		_registerClient(User &user);
		void		_joinChannel(User &user, std::string &channel, std::string &key);

		// messages
		std::string	RPL_WELCOME(User &user);
		std::string	RPL_YOURHOST(User &user);
		std::string	RPL_CREATED(User &user);
		std::string	RPL_MYINFO(User &user);
		std::string	RPL_ISUPPORT(User &user);
		std::string	RPL_UMODEIS(User &user);
		std::string	RPL_LUSERCLIENT(User &user);
		std::string	RPL_LUSEROP(User &user);
		std::string	RPL_LUSERUNKNOWN(User &user);
		std::string	RPL_LUSERCHANNELS(User &user);
		std::string	RPL_LUSERME(User &user);
		std::string	RPL_LOCALUSERS(User &user);
		std::string	RPL_GLOBALUSERS(User &user);
		std::string RPL_VERSION(User &user);
		std::string RPL_MOTD(User &user, std::string msg);
		std::string RPL_MOTDSTART(User &user);
		std::string RPL_ENDOFMOTD(User &user);
		std::string ERR_NOSUCHSERVER(User &user);
		std::string ERR_TOOMANYCHANNELS(User &user, std::string const &channel);
		std::string ERR_INPUTTOOLONG(User &user);
		std::string ERR_UNKNOWNCOMMAND(User &user, std::string const &);
		std::string ERR_NOMOTD(User &user);
		std::string ERR_NONICKNAMEGIVEN(User &user);
		std::string ERR_ERRONEUSNICKNAME(User &user);
		std::string ERR_NICKNAMEINUSE(User &user);
		std::string ERR_NOTREGISTERED(User &user);
		std::string ERR_NEEDMOREPARAMS(User &user, std::string command);
		std::string ERR_ALREADYREGISTERED(User &user);
		std::string ERR_PASSWDMISMATCH(User &user);
		std::string ERR_CHANNELISFULL(User &user, std::string const &channel);
		std::string ERR_INVITEONLYCHAN(User &user, std::string const &channel);
		std::string ERR_BADCHANNELKEY(User &user, std::string const &channel);
		std::string ERR_BADCHANMASK(User &user);
		std::string ERROR(std::string msg);
		std::string	PONG(std::string &token);
		std::string	_numeric(User &, std::string, std::string &, std::string);
		std::string	_getDate();
		std::string	_ISupportTokens();
};

class	emptyException: public std::exception
{
	virtual const char	*what() const throw()
	{
		return (NULL);
	}

};

std::string	getFirstWord(std::string &str);
std::string	itos(int const &i);
void		strToupper(std::string &str);
bool		is_valid_nick(std::string nick);
