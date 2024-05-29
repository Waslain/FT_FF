#pragma once

#include <string>

#define RN "\r\n"

#define	BASE(user, numeric)	\
std::string(std::string(":localhost ") + numeric + " " + (user.getNickname().empty() ? "*" : user.getNickname() + " "))

#define ERR_NEEDMOREPARAMS(user, command) \
std::string(BASE(user, "461") + command + " :Not enough parameters" + RN)

#define ERR_ALREADYREGISTERED(user) \
std::string(BASE(user, "462") + " : You may not reregister" + RN)

#define ERR_PASSWDMISMATCH(user) \
std::string(BASE(user, "464") + " :Password incorrect" + RN)

#define ERR_NONICKNAMEGIVEN(user) \
std::string(BASE(user, "431") + " :No nickname given" + RN)

#define ERR_ERRONEUSNICKNAME(user) \
std::string(BASE(user, "432") + " :Erroneus nickname" + RN)

#define ERR_NICKNAMEINUSE(user) \
std::string(BASE(user, "433") + " :Nickname is already in use" + RN)

#define ERR_NICKCOLLISION(user) \
std::string(BASE(user, "436") + " :Nickname collision KILL from ???") //Need to fix
