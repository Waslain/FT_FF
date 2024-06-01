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

void Server::_parseInput(std::string &str, int const &fd)
{
	std::string	cmd = getFirstWord(str);
	if (cmd.empty())
	{
		if (DEBUG == 1)
			std::cerr << "Received empty string" << std::endl;
		return ;
	}
	if (DEBUG) {
		std::cout << "cmd: " << cmd << std::endl;
		std::cout << "args: " << str << std::endl;
	}

	if (_cmdmap[cmd] != NULL)
		(*this.*_cmdmap[cmd])(fd, str);
}
