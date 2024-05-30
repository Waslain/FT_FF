/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/30 16:19:29 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_initCmdMap()
{
	_cmdmap["CAP"] = &Server::_CAP;
	_cmdmap["PASS"] = &Server::_PASS;
	_cmdmap["NICK"] = &Server::_NICK;
	_cmdmap["USER"] = &Server::_USER;
	_cmdmap["PING"] = &Server::_PING;
}

Server::Server(std::string port, std::string password): _pass(password), _time(time(NULL))
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

void	Server::_addClientMessage(User &user, std::string const &msg)
{
	std::string	tmp = user.getSendBuf() + msg;
	user.setSendBuf(tmp);
}

std::string	Server::_getTime()
{
	std::string			str;
	std::string			tmp;
	std::stringstream	ss;
	struct tm 			*tm = localtime(&this->_time);

	ss << tm->tm_mday << " ";
	ss << (tm->tm_mon + 1) << " ";
	ss << (tm->tm_year + 1900) << " ";
	ss << tm->tm_hour << " ";
	ss << tm->tm_min;

	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp + "-";
	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp + "-";
	ss >> tmp;
	str += tmp + " ";
	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp + ":";
	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp;

	return (str);

}
