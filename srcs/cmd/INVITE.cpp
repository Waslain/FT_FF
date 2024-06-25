/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:29:15 by fduzant           #+#    #+#             */
/*   Updated: 2024/06/13 15:44:34 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_INVITE(int const &fd, std::string &args)
{
	User &user = _users[fd];

	if (DEBUG)
	{
		std::cout << "[DEBUG] INVITE received from user[" << fd << "]" << std::endl;
		std::cout << "[DEBUG] ARGS STRING -> \"" << args << "\"" << std::endl;
	}

	std::vector<std::string> splited = split(args, ' ');
	if (splited.size() < 2)
	{
		_addClientMessage(user, ERR_NEEDMOREPARAMS(user, "INVITE"));
		return ;
	}

	if (DEBUG)
	{
		for (size_t i = 0; i < splited.size(); i ++)
			std::cout << "[DEBUG] SPLITED[" << i << "] -> " << splited[i] << std::endl;
	}

	std::string	target = splited[0];
	std::string	channel = splited[1];

	if (DEBUG)
	{
		std::cout << "[DEBUG] Target -> " << target << std::endl;
		std::cout << "[DEBUG] Channel -> " << channel << std::endl;
	}

	if (_channels.find(channel) == _channels.end())
	{
		if (DEBUG)
			std::cout << "[DEBUG] INVITE: channel not found" << std::endl;
		_addClientMessage(user, ERR_NOSUCHCHANNEL(user, channel));
		return ;
	}
	else {
		Channel &chan = _channels[channel];
		if (DEBUG)
		{
			std::cout << "[DEBUG] INVITE: channel found" << std::endl;
			std::cout << "[DEBUG] INVITE: channel name from chan class -> " << chan.getName() << std::endl;
		}
		try {
			User &targetUser = getUserByNick(target);
			if (chan.getUsers(user).find(user.getNickname()) == std::string::npos)
			{
				if (DEBUG)
					std::cout << "[DEBUG] INVITE: user not in channel" << std::endl;
				_addClientMessage(user, ERR_NOTONCHANNEL(user, channel));
				return ;
			}
			else {
				if (DEBUG)
					std::cout << "[DEBUG] INVITE: user in channel" << std::endl;
				if (chan.getMode('i') == true)
				{
					if (user.isOperator(channel))
						if (chan.getUsers(targetUser).find(targetUser.getNickname()) == std::string::npos)
						{
							_addChannelMessage(targetUser, chan, RPL_INVITING(targetUser, target, channel), OTHER);
							chan.addUserInInviteList(targetUser);
						}
						else
							_addClientMessage(user, ERR_USERONCHANNEL(user, channel));
					else
						_addClientMessage(user, ERR_CHANOPRIVSNEEDED(user, channel));
				}
				else
				{
					if (chan.getUsers(targetUser).find(targetUser.getNickname()) == std::string::npos)
					{
						_addChannelMessage(targetUser, chan, RPL_INVITING(targetUser, target, channel), OTHER);
						chan.addUserInInviteList(targetUser);
					}
					else
						_addClientMessage(user, ERR_USERONCHANNEL(user, channel));
				}
			}
		}catch (std::exception &e) {
			if (e.what())
				_addClientMessage(user, ERR_NOSUCHNICK(user, target));
		}
	}
}