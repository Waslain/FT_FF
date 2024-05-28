#include "Server.hpp"

void PrintTestFunction(int const &fd, std::vector<std::string>	&args)
{
	std::cout << "Test function called" << std::endl;
	(void)fd;
	(void)args;
}

void Server::_initCmdMap()
{
	// std::string cmd = "TEST";
	// _cmdmap[cmd] = &PrintTestFunction;
	_cmdmap["TEST"] = &PrintTestFunction;
}

template <typename T>
static void PrintVectArgs(std::vector<T> args)
{
	for (long unsigned int i = 0; i < args.size(); i++)
		std::cout << "Arg " << i << ": " << args[i] << std::endl;
}

void Server::parseInput(std::string &str, int const &fd)
{
	if (str.empty())
	{
		if (DEBUG == 1)
			std::cerr << "Received empty string" << std::endl;
		return ;
	}
	std::cout << "Received: " << str << std::endl;
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

	std::string s;
	std::stringstream ss(str);
	std::vector<std::string> args;
	while (getline(ss, s, ' '))
	{
		args.push_back(s);
	}
	//print args if DEBUG
	if (DEBUG == 1)
		PrintVectArgs(args);
	if (_cmdmap[args[0]] != NULL)
		_cmdmap[args[0]](fd, args);
}
