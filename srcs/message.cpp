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
	std::string	msg = "This server was created " + _getDate();
	return (_numeric(user, "", msg, "003"));
}

std::string	Server::RPL_MYINFO(User &user)
{
	std::string	msg = std::string(HOSTNAME) + " " + VERSION + " " + USERMODES + " " + CHANMODES;
	return (_numeric(user, "", msg, "004"));
}

std::string	Server::RPL_ISUPPORT(User &user)
{
	std::string str = _ISupportTokens();
	std::string	msg = "are supported by this server";
	return (_numeric(user, str, msg, "005"));
}

std::string	Server::RPL_UMODEIS(User &user)
{
	std::string	msg = ":localhost 221 ";
	msg += (user.getNickname().empty()) ? "*" : user.getNickname() + " ";
	std::string	modes = USERMODES;
	size_t		size = modes.size();
	for (size_t i = 0; i < size; i++) {
		if (user.getMode(modes[i])) {
			msg += modes[i];
		}
	}
	msg += + "\r\n";
	return (msg);
}

std::string	Server::RPL_LUSERCLIENT(User &user)
{
	std::string	msg = std::string("There ") + ((_nbUsers != 1) ? "are " : "is ") + itos(_nbUsers);
	msg += std::string(" user") + ((_nbUsers != 1) ? "s" : "") + " and " + itos(_nbIUsers) + " invisible on 1 server";
	return (_numeric(user, "", msg, "251"));
}

std::string	Server::RPL_LUSEROP(User &user)
{
	std::string	str = itos(_nbOperators) + " ";
	std::string	msg = std::string("operator") + ((_nbOperators != 1) ? "s" : "") + " online";
	return (_numeric(user, str, msg, "252"));
}

std::string	Server::RPL_LUSERUNKNOWN(User &user)
{
	std::string	str = itos(_nbUConnections) + " ";
	std::string	msg = std::string("unknown connection") + ((_nbUConnections != 1) ? "s" : "");
	return (_numeric(user, str, msg, "253"));
}

std::string	Server::RPL_LUSERCHANNELS(User &user)
{
	std::string	str = itos(_nbChannels) + " ";
	std::string	msg = std::string("channel") + ((_nbUConnections != 1) ? "s" : "") + " formed";
	return (_numeric(user, str, msg, "254"));
}

std::string	Server::RPL_LUSERME(User &user)
{
	std::string	msg = std::string("I have ") + itos(_nbUsers) + " client" +((_nbUsers != 1) ? "s" : "") + " and 0 servers";
	return (_numeric(user, "", msg, "255"));
}

std::string	Server::RPL_LOCALUSERS(User &user)
{
	std::string	str = itos(_nbUsers) + " " + itos(_maxUsers) + " ";
	std::string	msg = std::string("Current local users ") + itos(_nbUsers) + ", max " + itos(_maxUsers);
	return (_numeric(user, str, msg, "265"));
}

std::string	Server::RPL_GLOBALUSERS(User &user)
{
	std::string	str = itos(_nbUsers) + " " + itos(_maxUsers) + " ";
	std::string	msg = std::string("Current global users ") + itos(_nbUsers) + ", max " + itos(_maxUsers);
	return (_numeric(user, str, msg, "266"));
}

std::string Server::RPL_VERSION(User &user)
{
	std::string	str = VERSION + " " + HOSTNAME + " ";
	std::string	msg = "";
	return (_numeric(user, str, msg, "351"));
}

std::string Server::RPL_MOTD(User &user, std::string msg)
{
	return (_numeric(user, "", msg, "372"));
}

std::string Server::RPL_MOTDSTART(User &user)
{
	std::string	msg = HOSTNAME + " Message of the day -";
	return (_numeric(user, "", msg, "375"));
}

std::string Server::RPL_ENDOFMOTD(User &user)
{
	std::string	msg = "End of MOTD";
	return (_numeric(user, "", msg, "376"));
}

std::string Server::ERR_NOSUCHSERVER(User &user)
{
	std::string	msg = "No such server";
	return (_numeric(user, "", msg, "402"));
}

std::string Server::ERR_NOMOTD(User &user)
{
	std::string	msg = "MOTD file is missing";
	return (_numeric(user, "", msg, "422"));
}

std::string Server::ERR_NONICKNAMEGIVEN(User &user)
{
	std::string	msg = "No nickname given";
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

	msg = ":localhost " + numeric + " ";
	msg += (user.getNickname().empty()) ? "*" : user.getNickname() + " ";
	msg += str1 + ":" + str2 + "\r\n";
	return (msg);
}

std::string	Server::_getDate()
{
	std::string			str;
	std::string			tmp;
	std::stringstream	ss;
	struct tm 			*tm = localtime(&_time);

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

std::string	Server::_ISupportTokens()
{
	std::string	msg = std::string("AWAYLEN=") + itos(AWAYLEN) + " ";
	msg += std::string("CHANLIMIT=#:") + itos(CHANLIMIT) + " ";
	// CHANMODES
	msg += std::string("CHANNELLEN=") + itos(CHANNELLEN) + " ";
	msg += std::string("CHANTYPES=# ");
	// ELIST
	// EXCEPTS 
	// EXTBAN
	msg += std::string("HOSTLEN=") + itos(HOSTLEN) + " ";
	// INVEX
	msg += std::string("KICKLEN=") + itos(KICKLEN) + " ";
	// MAXLIST
	// MAXTARGETS
	// MODES
	msg += std::string("NICKLEN=") + itos(NICKLEN) + " ";
	// PREFIX
	// SAFELIST
	// SILENCE
	// STATUSMSG
	// TARGMAX
	msg += std::string("TOPICLEN=") + itos(TOPICLEN) + " ";
	msg += std::string("USERLEN=") + itos(USERLEN) + " ";
	return (msg);
}

std::string	itos(int const &i)
{
	std::stringstream	ss;
	std::string			s;
	ss << i;
	ss >> s;
	return (s);
}
