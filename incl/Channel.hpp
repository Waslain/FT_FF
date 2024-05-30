#pragma once

#include "Server.hpp"

class	User;

class	Channel
{
	public:
		Channel();
		Channel(Channel const &);
		~Channel() {};
		Channel	&operator=(Channel const &);

	private:
		std::string			_name;
};
