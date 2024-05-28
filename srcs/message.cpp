#include "Server.hpp"

std::string	joinArgs(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end)
{
	std::string	str = "";

	if (it == end) {
		return (str);
	}

	while (true)
	{
		str += *it;
		if (it + 1 == end) {
			break ;
		}
		str += " ";
		it++;
	}
	return (str);
}

void	Server::_PASS(int const &fd, std::vector<std::string> &args)
{
	(void)fd;

	std::string	pass = joinArgs(args.begin(), args.end());
	if (DEBUG) {
		std::cout << "password received: " << pass << std::endl;
	}
	if (pass == this->_pass) {
		std::cout << "password correct" << std::endl;
	}
}

void	Server::_CAP(int const &fd, std::vector<std::string> &args)
{
	static_cast<void>(fd);
	static_cast<void>(args);
}

void Server::_initCmdMap()
{
	_cmdmap["PASS"] = &Server::_PASS;
	_cmdmap["CAP"] = &Server::_CAP;
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

	std::string	cmd;
	if (getline(ss, s, ' ')) {
		cmd = s;
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
