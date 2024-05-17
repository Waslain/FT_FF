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
#include <netdb.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

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

		std::string _pass;
		std::string	_host;
		std::string	_port;
		int 		_socket;
		sockaddr_in _address;

		void	_getSocket();
};

class	emptyException: public std::exception
{
	public:
		virtual const char	*what() const throw()
		{
			return (NULL);
		}
};

