#pragma once

#include <string>

#define VERSION "ft_ff-1.0"
#define HOSTNAME "ft_ff"
#define	USERMODES "i"
#define	CHANMODES ""

#define RN "\r\n"

#define	BASE(user, numeric)	\
std::string(std::string(":localhost ") + numeric + " " + (user.getNickname().empty() ? "*" : user.getNickname() + " "))


#define RPL_WELCOME(user) \
std::string(BASE(user, "001") + ":Welcome to " + HOSTNAME + ", " + user.getNickname() + RN)

#define RPL_YOURHOST(user) \
std::string(BASE(user, "002") + ":Your host is " + HOSTNAME + ", running version " + VERSION + RN)

#define RPL_CREATED(user, date) \
std::string(BASE(user, "003") + ":This server was created " + date + RN)

#define RPL_MYINFO(user) \
std::string(BASE(user, "004") + HOSTNAME + " " + VERSION + " " + USERMODES + " " + CHANMODES + RN)

#define ERR_NONICKNAMEGIVEN(user) \
std::string(BASE(user, "431") + " :No nickname given" + RN)

#define ERR_ERRONEUSNICKNAME(user) \
std::string(BASE(user, "432") + " :Erroneus nickname" + RN)

#define ERR_NICKNAMEINUSE(user) \
std::string(BASE(user, "433") + " :Nickname is already in use" + RN)

#define ERR_NICKCOLLISION(user) \
std::string(BASE(user, "436") + " :Nickname collision KILL from ???" + RN) //Need to fix

#define ERR_NEEDMOREPARAMS(user, command) \
std::string(BASE(user, "461") + command + " :Not enough parameters" + RN)

#define ERR_ALREADYREGISTERED(user) \
std::string(BASE(user, "462") + " : You may not reregister" + RN)

#define ERR_PASSWDMISMATCH(user) \
std::string(BASE(user, "464") + " :Password incorrect" + RN)

#define	ERROR(msg) \
std::string(std::string("ERROR :") + msg + RN)
