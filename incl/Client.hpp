#pragma once

#include "Server.hpp"

class Server;

class	Client
{
	public:
		Client();
		Client(std::string const &, sockaddr_storage const &);
		~Client() { };

		void		setNickname(std::string const &) const;
		std::string	getNickname() const;

	private:
		Client(Client const &);
		Client	&operator=(Client const &);

		std::string			_nickname;
};
