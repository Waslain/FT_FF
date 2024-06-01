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
	
		void					setName(std::string const &);
		void					setTopic(std::string const &);
		void					setMode(char const &, bool const &);

		std::string				getName() const;
		std::string				getTopic() const;
		bool					getMode(char const &) const;

		void					addUser(User &);
		void					removeUser(User &);

	private:
		std::string				_name;
		std::string				_topic;
		std::map<char, bool>	_modes;
		std::vector<User *>		_users;

		typedef std::vector<User *>::iterator	userIt;
};
