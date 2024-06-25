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
	std::string	str;
	std::string	modes = USERMODES;
	size_t		size = modes.size();
	for (size_t i = 0; i < size; i++) {
		if (user.getMode(modes[i])) {
			str += modes[i];
		}
	}
	return (_numeric(user, str, "", "221"));
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

std::string Server::RPL_CHANNELMODEIS(User &user, std::string const &channame)
{
	Channel	&channel = _channels[channame];
	std::string	str = channame + " ";
	std::string	modes = CHANMODES;
	for (size_t i = 0; i < modes.size(); i++) {
		if (channel.getMode(modes[i])) {
			str += modes[i];
		}
	}
	std::string	params;
	std::string	key = channel.getKey();
	if (key.empty() == false) {
		str += 'k';
		params += std::string(" ") + key;
	}
	int	l = channel.getUserLimit();
	if (l != -1) {
		str += 'l';
		params += std::string(" ") + itos(l);
	}
	str += params;
	return (_numeric(user, str, "", "324"));
}

std::string Server::RPL_NOTOPIC(User &user, Channel &channel)
{
	std::string	str = channel.getName() + " ";
	std::string	msg = "No topic is set";
	return (_numeric(user, str, msg, "332"));
}

std::string Server::RPL_TOPIC(User &user, Channel &channel)
{
	std::string	str = channel.getName() + " ";
	std::string	msg = channel.getTopic();
	return (_numeric(user, str, msg, "332"));
}

std::string Server::RPL_TOPICWHOTIME(User &user, Channel &channel)
{
	std::string	str = channel.getName() + " " + channel.getTopicWho() + " " + itos(channel.getTopicTime()) + " ";
	std::string	msg = "";
	return (_numeric(user, str, msg, "333"));
}

std::string Server::RPL_INVITING(User &user, std::string const &nick, std::string const &channel)
{
	std::string	str = nick + " " + channel + " ";
	return (_numeric(user, str, "", "341"));
}

std::string Server::RPL_VERSION(User &user)
{
	std::string	str = VERSION + " " + HOSTNAME + " ";
	std::string	msg = "";
	return (_numeric(user, str, msg, "351"));
}

std::string Server::RPL_NAMEREPLY(User &user, std::string const &channame)
{
	std::string	str = std::string("= ") + channame + " ";
	std::string	msg = _channels[channame].getUsers(user);
	return (_numeric(user, str, msg, "353"));
}

std::string Server::RPL_ENDOFNAMES(User &user, std::string const &channame)
{
	std::string	str = channame + " ";
	std::string	msg = "End of /NAMES list";
	return (_numeric(user, str, msg, "366"));
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

std::string Server::ERR_NOSUCHNICK(User &user, std::string const &nick)
{
	std::string	str = nick + " ";
	std::string	msg = "No such nick/channel";
	return (_numeric(user, str, msg, "401"));
}

std::string Server::ERR_NOSUCHSERVER(User &user, std::string const &server)
{
	std::string	str = server + " ";
	std::string	msg = "No such server";
	return (_numeric(user, str, msg, "402"));
}

std::string Server::ERR_NOSUCHCHANNEL(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "No such channel";
	return (_numeric(user, "", msg, "403"));
}

std::string Server::ERR_CANNOTSENDTOCHAN(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "Cannot send to channel";
	return (_numeric(user, "", msg, "404"));
}

std::string Server::ERR_TOOMANYCHANNELS(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "You have joined too many channels";
	return (_numeric(user, "",  msg, "405"));
}

std::string Server::ERR_NORECIPIENT(User &user, std::string const &command)
{
	std::string	msg = "No recipient given (" + command + ")";
	return (_numeric(user, "", msg, "411"));
}

std::string Server::ERR_NOTEXTTOSEND(User &user)
{
	std::string	msg = "No text to send";
	return (_numeric(user, "",  msg, "412"));
}

std::string Server::ERR_INPUTTOOLONG(User &user)
{
	std::string	msg = "Input line was too long";
	return (_numeric(user, "", msg, "417"));
}

std::string Server::ERR_UNKNOWNCOMMAND(User &user, std::string const &cmd)
{
	std::string	msg = cmd + ": Unknown command";
	return (_numeric(user, "", msg, "421"));
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

std::string Server::ERR_USERNOTINCHANNEL(User &user, std::string const &nick, std::string const &channel)
{
	std::string str = nick + " " + channel + " ";
	std::string	msg = "They're not on that channel";
	return (_numeric(user, "", msg, "442"));
}

std::string Server::ERR_NOTONCHANNEL(User &user, std::string const &channel)
{
	std::string str = channel + " ";
	std::string	msg = "You're not on that channel";
	return (_numeric(user, "", msg, "442"));
}

std::string Server::ERR_USERONCHANNEL(User &user, std::string const &channel)
{
	std::string str = channel + " ";
	std::string	msg = "is already on channel";
	return (_numeric(user, "", msg, "443"));
}

std::string Server::ERR_NOTREGISTERED(User &user)
{
	std::string	msg = "You have not registered";
	return (_numeric(user, "", msg, "451"));
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

std::string Server::ERR_CHANNELISFULL(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "Channot join channel (+l)";
	return (_numeric(user, str,  msg, "471"));
}

std::string Server::ERR_INVITEONLYCHAN(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "Channot join channel (+i)";
	return (_numeric(user, str,  msg, "473"));
}

std::string Server::ERR_BADCHANNELKEY(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "Cannot join channel (+k)";
	return (_numeric(user, str,  msg, "475"));
}

std::string Server::ERR_BADCHANMASK(User &user)
{
	std::string	msg = "Bad Channel Mask";
	return (_numeric(user, "",  msg, "476"));
}

std::string Server::ERR_CHANOPRIVSNEEDED(User &user, std::string const &channel)
{
	std::string	str = channel + " ";
	std::string	msg = "You're not channel operator";
	return (_numeric(user, str,  msg, "482"));
}

std::string Server::ERR_UMODEUNKNOWNFLAG(User &user)
{
	std::string	msg = "Unkown MODE flag";
	return (_numeric(user, "",  msg, "501"));
}

std::string Server::ERR_USERDONTMATCH(User &user)
{
	std::string	msg = "Can't change mode for other users";
	return (_numeric(user, "",  msg, "502"));
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

std::string	Server::JOIN(User &user, std::string const &channel)
{
	std::string	msg = std::string(":") + user.getNickname() + "!" + user.getUsername() + "@localhost JOIN " + channel + "\r\n";
	return (msg);
}

std::string	Server::PRIVMSG(User &user, std::string const &target, std::string const &pvmsg)
{
	std::string msg = std::string(":") + user.getNickname() + "!" + user.getUsername() + "@localhost PRIVMSG " + target + " " + pvmsg + "\r\n"; 
	return (msg);
}

std::string	Server::KICK(User &user, std::string const &channel, std::string const &target, std::string const &comment)
{
	std::string	msg = std::string(":") + user.getNickname() + "!" + user.getUsername() + "@localhost KICK " + channel + " " + target + " " + comment + "\r\n";
	return (msg);
}

std::string	Server::PART(User &user, std::string const &channel, std::string const &reason)
{
	std::string	msg = std::string(":") + user.getNickname() + "!" + user.getUsername() + "@localhost PART " + channel + (reason.empty() ? "" : " ") + reason + "\r\n";
	return (msg);
}

std::string	Server::MODE(User &user, std::string const &target, std::string const &set)
{
	std::string	msg = std::string(":") + user.getNickname() + "!" + user.getUsername() + "@localhost MODE " + target + " " + set + "\r\n";
	return (msg);
}

std::string	Server::_numeric(User &user, std::string const &str1, std::string const &str2, std::string numeric)
{
	std::string	msg;

	msg = ":localhost " + numeric + " ";
	msg += (user.getNickname().empty()) ? "*" : user.getNickname() + " ";
	msg += str1 + (str2.empty() ? "" : ":") + str2 + "\r\n";
	return (msg);
}

std::string	Server::_getDate()
{ std::string			str;
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
	msg += std::string("PREFIX=(o)@ ");
	// SAFELIST
	// SILENCE
	// STATUSMSG
	// TARGMAX
	msg += std::string("TOPICLEN=") + itos(TOPICLEN) + " ";
	msg += std::string("USERLEN=") + itos(USERLEN) + " ";
	return (msg);
}
