/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:32:13 by fduzant           #+#    #+#             */
/*   Updated: 2024/06/06 19:16:09 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_KICK(int const &fd, std::string &args)
{
	User	&user = _users[fd];

	if (DEBUG) {
		std::cout << "[DEBUG] KICK received from user[" << fd << "]" << std::endl;
		std::cout << "[DEBUG] ARGS STRING -> \"" << args << "\"" << std::endl;
	}

	std::vector<std::string> splited = split(args, ' ');
	if (splited.size() < 2)
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "KICK"));
		return ;
	}

	if (DEBUG)
	{
		for (size_t i = 0; i < splited.size(); i ++)
			std::cout << "[DEBUG] SPLITED[" << i << "] -> " << splited[i] << std::endl;
	}

	std::string	channel = splited[0];
	std::string target = splited[1];
	std::string	comment = "You have been kicked from the channel";
	if (splited.size() > 2 && splited[2][0] == ':')
	{
		if (DEBUG)
			std::cout << "[DEBUG] Splited[2].size() == " << splited[2].size() << std::endl;
		if (splited[2].size() != 1)
		{
			comment = splited[2].substr(1);
			for (size_t i = 3; i < splited.size(); i++)
			{
				comment += " " + splited[i];
			}
		} 
	}

	if (DEBUG)
	{
		std::cout << "[DEBUG] Channel -> " << channel << std::endl;
		std::cout << "[DEBUG] Tagert -> " << target << std::endl;
		std::cout << "[DEBUG] Comment -> " << comment << std::endl;
	}

	if (_channels.find(channel) == _channels.end()) {
		// not found
		if (DEBUG)
			std::cout << "[DEBUG] Channel not found" << std::endl;
		_addClientMessage(user, ERR_NOSUCHCHANNEL(user, channel));
		return ;
	}
	else {
		// found
		Channel	&chan = _channels[channel];
		if (DEBUG)
		{
			std::cout << "[DEBUG] Channel found" << std::endl;
			std::cout << "[DEBUG] Channel name from chan class -> " << chan.getName() << std::endl;
		}
		try {
			User &targetUser = getUserByNick(target);
			if (chan.getUsers(user).find(user.getNickname()) == std::string::npos) {
				// not found
				if (DEBUG)
					std::cout << "[DEBUG] User not in channel" << std::endl;
				_addClientMessage(user, ERR_NOTONCHANNEL(user, channel));
				return ;
			}
			else {
				// found
				if (DEBUG)
					std::cout << "[DEBUG] User is in channel" << std::endl;
				if (user.isOperator(channel))
				{
					_addChannelMessage(user, chan, KICK(user, channel, target, comment), ALL);
					chan.removeUser(targetUser);
					targetUser.leaveChannel(chan);
				}
				else
					_addClientMessage(user, ERR_CHANOPRIVSNEEDED(user, channel));
			}
		}catch (std::exception &e) {
			if (DEBUG)
				std::cout << "[DEBUG] Exception Catched, target not found" << std::endl;
			if (e.what())
				_addClientMessage(user, ERR_NOSUCHNICK(user, target));
		}
	}
}