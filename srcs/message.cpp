#include "Server.hpp"

void PrintTestFunction()
{
	std::cout << "Test function called" << std::endl;
}

void Server::_initCmdMap()
{
	// std::string cmd = "TEST";
	// _cmdmap[cmd] = &PrintTestFunction;
	_cmdmap["TEST"] = &PrintTestFunction;
}

template <typename T>
void PrintVectArgs(std::vector<T> args)
{
	for (long unsigned int i = 0; i < args.size(); i++)
		std::cout << "Arg " << i << ": " << args[i] << std::endl;
}

void Server::parseInput(std::string str)
{
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
		_cmdmap[args[0]]();
}

