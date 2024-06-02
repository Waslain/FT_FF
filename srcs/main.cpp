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
#include <iomanip>

bool	run = true;

void	sigintHandler(int signal)
{
	if (signal == SIGINT) {
		run = false;
	}
}

void	setSignalAction()
{
	struct sigaction	act;
	bzero(&act, sizeof(act));
	act.sa_handler = &sigintHandler;
	sigaction(SIGINT, &act, NULL);
}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		std::cerr << RED <<  "Error: usage: ./ircserv <port> <password>" << RESETCOLOR << std::endl;
		return (1);
	}

	setSignalAction();

	try
	{
		Server	server(argv[1], argv[2]);
		server.loop();
	}
	catch (std::exception &e) {
		if (e.what())
			std::cerr <<  "Error: " << e.what() << std::endl;
	}
	return (1);
}
