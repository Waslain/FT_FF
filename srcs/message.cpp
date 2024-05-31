#include "Server.hpp"

std::string	Server::RPL_WELCOME(User &user)
{
	std::string	msg = std::string("Welcome to ") + HOSTNAME + ", " + user.getNickname();
	return (_numeric(user, "", msg, "001"));
}

std::string	Server::RPL_YOURHOST(User &user)
{
	std::string	msg = std::string("Your host is ") + HOSTNAME + ", running version " + VERSION;
	return (_numeric(user, "", msg, "002"));
}

std::string	Server::RPL_CREATED(User &user)
{
	std::string	msg = ("This server was created ") + _getDate();
	return (_numeric(user, "", msg, "003"));
}

std::string	Server::RPL_MYINFO(User &user)
{
	std::string	msg = std::string(HOSTNAME) + " " + VERSION + " " + USERMODES + " " + CHANMODES;
	return (_numeric(user, "", msg, "004"));
}

std::string	Server::RPL_ISUPPORT(User &user)
{
	std::string	msg = "are supported by this server";
	return (_numeric(user, "", msg, "005"));
}

std::string Server::ERR_NONICKNAMEGIVEN(User &user)
{
	std::string	msg = "No nickname givern";
	return (_numeric(user, "", msg, "431"));
}

std::string Server::ERR_ERRONEUSNICKNAME(User &user)
{
	std::string	msg = "Erroneus nickname";
	return (_numeric(user, "", msg, "432"));
}

std::string Server::ERR_NICKNAMEINUSE(User &user)
{
	std::string	msg = "Nickname is already in use";
	return (_numeric(user, "", msg, "433"));
}

std::string Server::ERR_NEEDMOREPARAMS(User &user, std::string command)
{
	std::string	msg = "Not enough parameter";
	return (_numeric(user, command, msg, "461"));
}

std::string Server::ERR_ALREADYREGISTERED(User &user)
{
	std::string	msg = "You may not reregister";
	return (_numeric(user, "", msg, "462"));
}

std::string Server::ERR_PASSWDMISMATCH(User &user)
{
	std::string	msg = "Password incorrect";
	return (_numeric(user, "",  msg, "464"));
}

std::string Server::ERROR(std::string reason)
{
	std::string	msg = "ERROR :" + reason + "\r\n";
	return (msg);
}

std::string	Server::PONG(std::string &token)
{
	std::string	msg = std::string("PONG ") + HOSTNAME + " " + token + "\r\n";
	return (msg);
}

std::string	Server::_numeric(User &user, std::string str1, std::string &str2, std::string numeric)
{
	std::string	msg;

	msg = ":localhost ";
	msg += numeric + " ";
	msg += (user.getNickname().empty()) ? "*" : user.getNickname() + " ";
	msg += str1 + " :";
	msg += str2;
	msg += "\r\n";
	return (msg);
}

std::string	Server::_getDate()
{
	std::string			str;
	std::string			tmp;
	std::stringstream	ss;
	struct tm 			*tm = localtime(&this->_time);

	ss << tm->tm_mday << " ";
	ss << (tm->tm_mon + 1) << " ";
	ss << (tm->tm_year + 1900) << " ";
	ss << tm->tm_hour << " ";
	ss << tm->tm_min;

	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp + "-";
	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp + "-";
	ss >> tmp;
	str += tmp + " at ";
	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp + ":";
	ss >> tmp;
	str += ((tmp.size() == 1) ? "0" : "") + tmp;

	return (str);

}
