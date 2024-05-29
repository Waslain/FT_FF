#include "Server.hpp"

template <typename T>
static void PrintVectArgs(std::vector<T> args)
{
	for (long unsigned int i = 0; i < args.size(); i++)
		std::cout << "Arg " << i << ": " << args[i] << std::endl;
}

void Server::parseInput(std::string &str, int const &fd)
{
	std::cout << "Received: " << str << std::endl;

	std::string s;
	std::stringstream ss(str);

	std::string	cmd;
	if (getline(ss, s, ' ')) {
		cmd = s;
	}

	if (cmd.empty())
	{
		if (DEBUG == 1)
			std::cerr << "Received empty string" << std::endl;
		return ;
	}

	std::vector<std::string> args;
	while (getline(ss, s, ' ')) {
		args.push_back(s);
	}
	//print args if DEBUG
	if (DEBUG == 1)
		PrintVectArgs(args);
	if (_cmdmap[cmd] != NULL)
		(*this.*_cmdmap[cmd])(fd, args);
}
