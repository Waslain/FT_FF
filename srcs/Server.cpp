/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/06/10 18:28:45 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_initCmdMap()
{
	_cmdmap["CAP"] = &Server::_CAP;
	_cmdmap["PASS"] = &Server::_PASS;
	_cmdmap["NICK"] = &Server::_NICK;	// not complete
	_cmdmap["USER"] = &Server::_USER;
	_cmdmap["PING"] = &Server::_PING;
	_cmdmap["QUIT"] = &Server::_QUIT;	// not complete
	_cmdmap["LUSERS"] = &Server::_LUSERS;
	_cmdmap["VERSION"] = &Server::_VERSION;
	_cmdmap["MOTD"] = &Server::_MOTD;
	_cmdmap["JOIN"] = &Server::_JOIN;
	_cmdmap["PART"] = &Server::_PART;
	_cmdmap["NAMES"] = &Server::_NAMES;
	_cmdmap["TOPIC"] = &Server::_TOPIC;
	_cmdmap["PRIVMSG"] = &Server::_PRIVMSG;
	_cmdmap["MODE"] = &Server::_MODE;

	//_cmdmap["OPER"] = &Server::_OPER;
	//_cmdmap["LIST"] = &Server::_LIST;
	_cmdmap["INVITE"] = &Server::_INVITE;
	_cmdmap["KICK"] = &Server::_KICK;
	//_cmdmap["ADMIN"] = &Server::_ADMIN;
	//_cmdmap["TIME"] = &Server::_TIME;
	//_cmdmap["STATS"] = &Server::_STATS;
	//_cmdmap["HELP"] = &Server::_HELP;
	//_cmdmap["INFO"] = &Server::_INFO;
	//_cmdmap["NOTICE"] = &Server::_NOTICE;
	//_cmdmap["WHO"] = &Server::_WHO;
	//_cmdmap["WHOIS"] = &Server::_WHOIS;
	//_cmdmap["WHOWAS"] = &Server::_WHOWAS;
	//_cmdmap["KILL"] = &Server::_KILL;
	//_cmdmap["SQUIT"] = &Server::_SQUIT;
	//_cmdmap["AWAY"] = &Server::_AWAY;
	//_cmdmap["USERHOST"] = &Server::_USERHOST;
	//_cmdmap["WALLOPS"] = &Server::_WALLOPS;
}

Server::Server(std::string port, std::string password): _pass(password), _nbUsers(0), _nbIUsers(0), _maxUsers(0), _nbOperators(0), _nbUConnections(0), _nbChannels(0), _time(time(NULL))
{
	_initCmdMap();
	_getSocket(port);
}

Server::~Server()
{
	close(_socket);
	std::vector<pollfd>::iterator	it = _pfds.begin();
	std::vector<pollfd>::iterator	ite = _pfds.end();
	for (; it < ite; it++) {
		close(it->fd);
	}
}

void	Server::_addClientMessage(User &user, std::string const &msg)
{
	std::string	tmp = user.getSendBuf() + msg;
	user.setSendBuf(tmp);
}

void	Server::_addChannelMessage(User &user, Channel &channel, std::string const &msg, int const &mode)
{
	channel.send(user, msg, mode);
}

Channel &Server::getChannel(const std::string &chan)
{
	chanIt	it = _channels.begin();
	chanIt	ite = _channels.end();
	for (; it != ite; it++) {
		if (it->second.getName() == chan) {
			if (DEBUG)
				std::cout << "[DEBUG] getChannel: channel found -> " << it->second.getName() << std::endl;
			return (it->second);
		}
	}
	throw std::runtime_error("getChannel: channel not found");
}

User &Server::getUserByNick(const std::string &nick)
{
	userIt	it = _users.begin();
	userIt	ite = _users.end();
	for (; it != ite; it++) {
		if (it->second.getNickname() == nick) {
			if (DEBUG)
			{
				std::cout << "[DEBUG] getUserByNick: user found -> " << it->second.getNickname() << std::endl;
				std::cout << "[DEBUG] getUserByNick: user fd -> " << it->second.getFd() << std::endl;
			}
			return (it->second);
		}
	}
	throw std::runtime_error("getUserByNick: user not found");
}

User *Server::_getUser(const std::string &nick)
{
	userIt	it = _users.begin();
	userIt	ite = _users.end();

	for (; it != ite; it++)
	{
		if (it->second.getNickname() == nick) {
			return (&(it->second));
		}
	}
	return (NULL);
}

bool	Server::_isNickOnServer(std::string const &nick) const
{
	userConstIt	it = _users.begin();
	userConstIt ite = _users.end();

	for (; it != ite; it++)
	{
		if (it->second.getNickname().compare(nick) == 0) {
			return (true);
		}
	}
	return (false);
}
