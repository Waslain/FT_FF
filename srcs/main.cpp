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
	if (argc < 3) {
		return (1);
	}

	Server	server(atoi(argv[1]), std::string(argv[2]));
	server.loop();

	return 0;
}
