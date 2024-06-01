#include "Channel.hpp"

Channel::Channel()
{
	std::string	mode = CHANMODE;
	size_t		size = mode.size();

	for (size_t i = 0; i < size; i++) {
		_mode[mode[i]] = false;
	}
}

Channel::~Channel()
{}

Channel::Channel(Channel const &cpy)
{
	*this = cpy;
}

Channel	&Channel::operator=(Channel const &cpy)
{
	_modes = cpy.modes;
	_users = cpy.users;
	return (*this);
}

void					Channel::setName(std::string const &name)
{
	_name = name;
}

void					Channel::setTopic(std::string const &topic)
{
	_topic = topic;
}

void					Channel::setMode(char const &mode, bool const &value)
{
	_modes[mode] = value;
}

std::string				Channel::getName() const
{
	return (_name);
}

std::string				Channel::getTopic() const
{
	return (_topic);
}

bool					Channel::getMode(char const &mode) const
{
	return (_modes[c]);
}

void					Channel::addUser(User &user)
{
	_users.push_back(&user);
}

void					Channel::removeUser(User &user)
{
	userIt	it = _users.begin();
	userIt	ite = _users.end();

	_users.erase(find(it, ite, &user));
}
