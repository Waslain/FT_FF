#pragma once

#include "Server.hpp"

class Server;
class Channel;

class	User
{
	public:
		User();
		User(int const &fd);
		User(User const &);
		~User();
		User	&operator=(User const &);

		void								setNickname(std::string const &);
		void								setUsername(std::string const &);
		void								setRealname(std::string const &);
		void								setPassword(std::string const &);
		void								setRecvBuf(std::string const &);
		void								setSendBuf(std::string const &);
		void								registerUser();
		void								setDisconnection();
		void								setMode(char const &, bool const &);

		int									getFd() const;
		std::string							getNickname() const;
		std::string							getUsername() const;
		std::string							getRealname() const;
		std::string							getPassword() const;
		std::string							getRecvBuf() const;
		std::string							getSendBuf() const;
		time_t								getTime() const;
		bool								isRegistered() const;
		bool								disconnect() const;
		bool								getMode(char const &);

	private:
		int									_fd;
		std::string							_nickname;
		std::string							_username;
		std::string							_realname;
		std::string							_password;
		std::string							_sendBuf;
		std::string 						_recvBuf;
		time_t 								_time;
		bool								_registered;
		bool								_disconnect;
		std::map<char, bool>				_mode;
		std::map<std::string, Channel *>	_channels;
};
