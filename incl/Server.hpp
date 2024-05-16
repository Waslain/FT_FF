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
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include "Server.hpp"

class Server
{
	public:
		Server(int port, std::string password);
		~Server();
		
		void	loop();

		// exception to throw when a function sets errno on failure
		class	errnoException: public std::exception
		{
			virtual const char	*what() const throw()
			{
				return (strerror(errno));
			}
		};

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
