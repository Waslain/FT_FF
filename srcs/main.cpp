#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		return (1);
	}

	int	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	(void)argv;
	serverAddress.sin_port = htons(atoi(argv[1]));
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	listen(serverSocket, 5);

	int	clientSocket = accept(serverSocket, NULL, NULL);

	char	buffer[1024] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);
	std::cout << "Message: " << buffer << std::endl;

	close(serverSocket);

	return 0;
}
