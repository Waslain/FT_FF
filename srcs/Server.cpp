/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/29 14:53:53 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_initCmdMap()
{
	_cmdmap["CAP"] = &Server::_CAP;
	_cmdmap["PASS"] = &Server::_PASS;
	_cmdmap["NICK"] = &Server::_NICK;
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

void	Server::_addClientMessage(User &user, std::string const &msg)
{
	std::string	tmp = user.getSendBuf() + msg;
	user.setSendBuf(tmp);
}
