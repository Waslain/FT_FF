#include "Channel.hpp"

Channel::Channel(): _nbUsers(0), _userLimit(-1)
{
	std::string	mode = CHANMODES;
	size_t		size = mode.size();

	for (size_t i = 0; i < size; i++) {
		_modes[mode[i]] = false;
	}
}

Channel::Channel(User &user, std::string const &name): _name(name), _nbUsers(0), _userLimit(-1)
{
	std::string	mode = CHANMODES;
	size_t		size = mode.size();

	for (size_t i = 0; i < size; i++) {
		_modes[mode[i]] = false;
	}

	addUser(user);
	addOperator(user);
}

Channel::~Channel()
{}

Channel::Channel(Channel const &cpy)
{
	*this = cpy;
}

Channel	&Channel::operator=(Channel const &cpy)
{
	_name = cpy._name;
	_topic = cpy._topic;
	_key = cpy._key;
	_modes = cpy._modes;
	_users = cpy._users;
	_operators = cpy._operators;
	_nbUsers = cpy._nbUsers;
	_userLimit = cpy._userLimit;
	return (*this);
}

void			Channel::setName(std::string const &name)
{
	_name = name;
}

void			Channel::setTopic(User &user, std::string const &topic)
{
	_topic = topic;
	_topicWho = user.getNickname();
	_topicTime = time(NULL);
}

void			Channel::setKey(std::string const &key)
{
	_key = key;
}

void			Channel::setMode(char const &mode, bool const &value)
{
	_modes[mode] = value;
}

void			Channel::setUserLimit(int const &limit)
{
	_userLimit = limit;
}

std::string		Channel::getName() const
{
	return (_name);
}

std::string		Channel::getTopic() const
{
	return (_topic);
}

std::string		Channel::getTopicWho() const
{
	return (_topicWho);
}

std::string		Channel::getKey() const
{
	return (_key);
}

bool			Channel::getMode(char const &mode)
{
	return (_modes[mode]);
}

int				Channel::getNbUsers() const
{
	return (_nbUsers);
}

int				Channel::getUserLimit() const
{
	return (_userLimit);
}

time_t			Channel::getTopicTime() const
{
	return (_topicTime);
}

bool			Channel::isOperator(User &user) const
{
	std::vector<User *>::const_iterator	it = _operators.begin();
	std::vector<User *>::const_iterator	ite = _operators.end();

	if (find(it, ite, &user) == ite) {
		return (false);
	}
	return (true);
}

void			Channel::addUser(User &user)
{
	_users.push_back(&user);
	_nbUsers++;
}

void			Channel::removeUser(User &user)
{
	userIt	it = _users.begin();
	userIt	ite = _users.end();
	userIt	itt = find(it, ite, &user);
	
	*itt = NULL;
	_users.erase(itt);
	_nbUsers--;
	if (isOperator(user)) {
		removeOperator(user);
	}
}

void			Channel::addOperator(User &user)
{
	_operators.push_back(&user);
}

void			Channel::removeOperator(User &user)
{
	userIt	it = _operators.begin();
	userIt	ite = _operators.end();
	userIt	itt = find(it, ite, &user);

	*itt = NULL;
	_operators.erase(itt);
}

void			Channel::send(std::string const &msg)
{
	userIt		it = _users.begin();
	userIt		ite = _users.end();
	std::string	str;

	for (; it != ite; it++)
	{
		str = (*it)->getSendBuf();
		str += msg;
		(*it)->setSendBuf(str);
	}
}