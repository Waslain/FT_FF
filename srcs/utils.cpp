#include "Server.hpp"

std::string	getFirstWord(std::string &str)
{
	std::string	s;
	size_t		pos = 0;

	pos = str.find(' ');
	if (pos == std::string::npos)
	{
		std::string	tmp = str;
		str.clear();
		return (tmp);
	}

	s = str.substr(0, pos);
	while (str[pos] == ' ') {
		pos++;
	}
	str.erase(0, pos);

	return  (s);
}

void	strToupper(std::string &str)
{
	for (size_t i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}
}

bool is_valid_nick(std::string nick)
{
	if (nick.size() > NICKLEN) {
		return (false);
	}
	std::string	set = ALPHA + SPECIAL;
	if (set.find_first_of(nick[0], 0) == std::string::npos) {
		return (false);
	}
	set += NUM + "-";
	if (nick.find_first_not_of(set, 1) != std::string::npos) {
		return (false);
	}
	return (true);
}

std::string	itos(int const &i)
{
	std::stringstream	ss;
	std::string			s;
	ss << i;
	ss >> s;
	return (s);
}
