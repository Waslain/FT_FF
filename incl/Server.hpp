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

class Server
{
	public:
		Server(int port, std::string password);
		~Server();
		
		Server &operator=(const Server &src);
	private:
		Server();
		Server(const Server &copy);
		std::string _pass;
		std::string _host;
		int _port;
		int _socket;
};