#include "User.hpp"

User::User()
{}

User::User(int const &fd): _fd(fd), _time(time(NULL)), _canRegister(false), _registered(false), _disconnect(false)
{
	std::string	mode = USERMODES;
	size_t		size = mode.size();

	for (size_t i = 0; i < size; i++) {
		_modes[mode[i]] = false;
	}
	_modes['i'] = true;
}

User::User(User const &cpy)
{
	*this = cpy;
}

User::~User()
{}

User	&User::operator=(User const &cpy)
{
	_fd = cpy._fd;
	_nickname = cpy._nickname;
	_username = cpy._username;
	_password = cpy._password;
	_canRegister = cpy._canRegister;
	_registered = cpy._registered;
	_disconnect = cpy._disconnect;
	_time = cpy._time;
	_modes = cpy._modes;
	return (*this);
}

void	User::setNickname(std::string const &nickname)
{
	_nickname = nickname;
}

void	User::setUsername(std::string const &username)
{
	_username = username;
}

void	User::setRealname(std::string const &realname)
{
	_realname = realname;
}

void	User::setPassword(std::string const &password)
{
	_password = password;
}

void	User::setRegistration(bool const &value)
{
	_canRegister = value;
}

void	User::registerUser()
{
	_registered = true;
}

void	User::setDisconnection()
{
	_disconnect = true;
}

void	User::setMode(char const &mode, bool const &value)
{
	_modes[mode] = value;
}

int			User::getFd() const
{
	return (_fd);
}

std::string	User::getNickname() const
{
	return (_nickname);
}

std::string	User::getUsername() const
{
	return (_username);
}

std::string	User::getRealname() const
{
	return (_realname);
}

std::string	User::getPassword() const
{
	return (_password);
}

bool	User::canRegister() const
{
	return (_canRegister);
}

bool	User::isRegistered() const
{
	return (_registered);
}

void		User::setRecvBuf(std::string const &str)
{
	_recvBuf = str;
}

void		User::setSendBuf(std::string const &str)
{
	_sendBuf = str;
}

std::string	User::getRecvBuf() const
{
	return (_recvBuf);
}

std::string	User::getSendBuf() const
{
	return (_sendBuf);
}

time_t		User::getTime() const
{
	return (_time);
}

bool		User::disconnect() const
{
	return (_disconnect);
}

bool		User::getMode(char const &mode)
{
	return (_modes[mode]);
}
