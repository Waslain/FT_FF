/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:26:49 by fduzant           #+#    #+#             */
/*   Updated: 2024/06/03 18:37:53 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_PRIVMSG(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (DEBUG) {
		std::cout << "PRIVMSG received from user[" << fd << "]" << std::endl;
	}
	if (user.isRegistered() == false || user.getNickname().empty())
	{
		std::cout << "PRIVMSG: user not registered" << std::endl;
		_addClientMessage(user, ERR_NOTREGISTERED(user));
		return ;
	}
	std::vector<std::string> splited = split(args, ' ');
	if (splited.size() == 0)
	{
		_addClientMessage(user, ERR_NORECIPIENT(user, "PRIVMSG"));
		return ;
	}
	if (splited.size() == 1)
	{
		_addClientMessage(user, ERR_NOTEXTTOSEND(user));
		return ;
	}

	std::string privmsg;
	if (splited.size() >= 2)
	{
		if (splited[1][0] == ':')
			splited[1].erase(0, 1);
		privmsg = buildmsg(splited);
		if (privmsg.empty())
		{
			_addClientMessage(user, ERR_NOTEXTTOSEND(user));
			return ;
		}
		
		if (DEBUG)
			std::cout << "PRIVMSG: message: " << privmsg << std::endl;
		_privmsgprocess(user, splited[0], privmsg);
	}
}

void Server::_privmsgprocess(User user, std::string &target, std::string &msg)
{
	if (target[0] == '#')
	{
		// channel
		// try {
		// 	Channel &target_channel = getChannel(target);
		// 	// _addClientMessage(target_channel, PRIVMSG(user, target_channel, msg));
		// }catch (std::exception &e) {
		// 	if (e.what())
		// 		// _addClientMessage(user, ERR_CANNOTSENDTOCHAN(user, target));
		// }                                                                    
	}
	else
	{
		// user
		try {
			User &target_user = getUserByNick(target);
			_addClientMessage(target_user, PRIVMSG(user, target_user, msg));
		}catch (std::exception &e) {
			if (e.what())
				_addClientMessage(user, ERR_NOSUCHNICK(user, target));
		}
	}
}