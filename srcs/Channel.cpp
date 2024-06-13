#include "Channel.hpp"

Channel::Channel()
{}

Channel::Channel(User &user, std::string const &name): _name(name), _nbUsers(0), _userLimit(-1)
{
	std::string	mode = CHANMODES;
	size_t		size = mode.size();

	for (size_t i = 0; i < size; i++) {
		_modes[mode[i]] = false;
	}

	_modes['t'] = true;

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

bool			Channel::getMode(char const &mode) const
{
	std::map<char, bool>::const_iterator	it = _modes.find(mode);
	if (it == _modes.end()) {
		return (false);
	}
	return (it->second);
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

std::string		Channel::getUsers(User const &user) const
{
	userConstIt	it = _users.begin();
	userConstIt	ite = _users.end();
	std::string	str;

	for (; it != ite; it++)
	{
		if ((*it)->getMode('i') == true && user.isOnChannel(_name) == false) {
			continue ;
		}
		str += ((*it)->isOperator(_name) ? "@" : "") + (*it)->getNickname();
		if (it + 1 == ite) {
			continue ;
		}
		str += " ";
	}
	return (str);
}

bool		Channel::IsUserInInviteList(User const &user) const
{
	userConstIt	it = _invitelist.begin();
	userConstIt	ite = _invitelist.end();

	if (find(it, ite, &user) == ite) {
		return (false);
	}
	return (true);
}

bool			Channel::isOperator(User const &user) const
{
	userConstIt	it = _operators.begin();
	userConstIt	ite = _operators.end();

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

void			Channel::addUserInInviteList(User &user)
{
	_invitelist.push_back(&user);
}

void			Channel::removeUserInInviteList(User &user)
{
	userIt it = _invitelist.begin();
	userIt ite = _invitelist.end();
	it = find(it, ite, &user);
	*it = NULL;
	_invitelist.erase(it);
}

void			Channel::removeUser(User &user)
{
	userIt	it = _users.begin();
	userIt	ite = _users.end();
	userIt	itt = find(it, ite, &user);
	
	// Remove user from invite list
	userIt it2 = _invitelist.begin();
	userIt ite2 = _invitelist.end();
	it2 = find(it2, ite2, &user);
	if (it2 != ite2) {
		*it2 = NULL;
		_invitelist.erase(it2);
	}
	// Remove user from invite list

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

void			Channel::send(User &source, std::string const &msg, int const &mode)
{
	userIt		it = _users.begin();
	userIt		ite = _users.end();
	std::string	str;

	for (; it != ite; it++)
	{
		if (mode == OTHER && *it == &source) {
			continue ;
		}
		str = (*it)->getSendBuf();
		str += msg;
		(*it)->setSendBuf(str);
	}
}
