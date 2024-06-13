#pragma once

#include "Server.hpp"

class	User;

class	Channel
{
	public:
		Channel();
		Channel(User &user, std::string const &);
		Channel(Channel const &);
		~Channel();
		Channel	&operator=(Channel const &);
	
		void					setName(std::string const &);
		void					setTopic(User &, std::string const &);
		void					setKey(std::string const &);
		void					setMode(char const &, bool const &);
		void					setUserLimit(int const &);

		std::string				getName() const;
		std::string				getTopic() const;
		std::string				getTopicWho() const;
		std::string				getKey() const;
		bool					getMode(char const &) const;
		int						getNbUsers() const;
		int						getUserLimit() const;
		time_t					getTopicTime() const;
		std::string				getUsers(User const &user) const;
		bool					IsUserInInviteList(User const &user) const;
		bool					isOperator(User const &user) const;

		void					addUser(User &);
		void					addUserInInviteList(User &user);
		void					removeUserInInviteList(User &);
		void					removeUser(User &);
		void					addOperator(User &);
		void					removeOperator(User &);
		void					send(User &source, std::string const &msg, int const &mode);

	private:
		std::string				_name;
		std::string				_topic;
		std::string				_topicWho;
		time_t					_topicTime;
		std::string				_key;
		int						_nbUsers;
		int						_userLimit;
		std::map<char, bool>	_modes;
		std::vector<User *>		_users;
		std::vector<User *>		_invitelist;
		std::vector<User *>		_operators;

		typedef std::vector<User *>::iterator		userIt;
		typedef std::vector<User *>::const_iterator	userConstIt;
};
