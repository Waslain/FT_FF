/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:42 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/16 19:28:14 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>

class Server
{
	public:
		Server(int port, std::string password);
		~Server();
		
		void	loop();

	private:
		Server();
		Server(const Server &copy);
		Server &operator=(const Server &src);

		std::string _pass;
		std::string	_host;
		int			_port;
		int 		_socket;
		sockaddr_in _address;
};
