/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:26:51 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/16 19:28:08 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Error: usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	try
	{
		Server	server(argv[1], argv[2]);
		//server.loop();
	}
	catch (std::exception &e) {
		if (e.what())
			std::cerr <<  "Error: " << e.what() << std::endl;
	}

	return (1);
}
