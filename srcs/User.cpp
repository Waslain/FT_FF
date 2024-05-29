#include "User.hpp"

User::User(): _registered(false)
{}

User::User(User const &cpy)
{
	*this = cpy;
}

User::~User()
{}

User	&User::operator=(User const &cpy)
{
	this->_nickname = cpy._nickname;
	this->_username = cpy._username;
	this->_password = cpy._password;
	this->_registered = cpy._registered;
	return (*this);
}

void	User::setNickname(std::string const &nickname)
{
	this->_nickname = nickname;
}

void	User::setUsername(std::string const &username)
{
	this->_username = username;
}

void	User::setPassword(std::string const &password)
{
	this->_password = password;
}

void	User::registerUser()
{
	this->_registered = true;
}

std::string	User::getNickname() const
{
	return (this->_nickname);
}

std::string	User::getUsername() const
{
	return (this->_username);
}

std::string	User::getPassword() const
{
	return (this->_password);
}

bool	User::isRegistered() const
{
	return (this->_registered);
}

void		User::setRecvBuf(std::string const &str)
{
	this->_recvBuf = str;
}

void		User::setSendBuf(std::string const &str)
{
	this->_sendBuf = str;
}

std::string	User::getRecvBuf() const
{
	return (this->_recvBuf);
}

std::string	User::getSendBuf() const
{
	return (this->_sendBuf);
}
