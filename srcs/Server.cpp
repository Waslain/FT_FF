/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:47 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/16 19:26:48 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	//std::cout << "Default Server constructor called" << std::endl;
}

Server::Server(const Server &copy)
{
	//std::cout << "Server copy constructor called" << std::endl;
}

Server::~Server()
{
	//std::cout << "Server deconstructor called" << std::endl;
}

Server &Server::operator=(const Server &src)
{
	if (this != &src)
	{
		//STUFF TO DO
	}
	return *this;
}