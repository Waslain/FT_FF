# IRC Server

This project implements an Internet Relay Chat (IRC) server in C++. It allows multiple clients to connect, communicate, and interact using standard IRC commands.

## Features

- Supports multiple IRC commands such as `JOIN`, `PART`, `PRIVMSG`, `NICK`, `QUIT`, `MOTD`, and more.
- Handles multiple clients simultaneously using `poll` for event-driven I/O.
- Implements user authentication with a password.
- Provides a modular structure for easy extension and maintenance.

## Project Structure

```
incl/
	Channel.hpp
	colors.hpp
	Message.hpp
	Server.hpp
	User.hpp
srcs/cmd/
	CAP.cpp
	INVITE.cpp
	JOIN.cpp
	KICK.cpp
	LUSERS.cpp
	MODE.cpp
	NAMES.cpp
	NICK.cpp
	PART.cpp
	PASS.cpp
	PING.cpp
	PRIVMSG.cpp
	QUIT.cpp
	TOPIC.cpp
	USER.cpp
	VERSION.cpp
```

- **incl/**: Contains header files for core classes and utilities.
- **srcs/**: Contains the implementation of the server and its components.
- **cmd/**: Contains the implementation of IRC commands.
- **motd**: The Message of the Day file displayed to users upon connection.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++98 or later.
- `make` build system.

### Building the Project

To build the project, run the following command:

```sh
make
```

### Running the Server

After building, you can run the server with:

```sh
./ircserv <port> <password>
```

- `<port>`: The port number the server will listen on.
- `<password>`: The password clients must provide to connect.

### Example

```sh
./ircserv 6667 mypassword
```

## Usage

Once the server is running, clients can connect using an IRC client (e.g., `irssi`, `weechat`, or `mIRC`) and interact using standard IRC commands.

### Supported Commands

- `PASS`: Authenticate with the server.
- `NICK`: Set or change the nickname.
- `USER`: Register a new user.
- `JOIN`: Join a channel.
- `PART`: Leave a channel.
- `PRIVMSG`: Send a private message.
- `QUIT`: Disconnect from the server.
- `MOTD`: View the Message of the Day.
- And more...

## Configuration

- **Message of the Day (MOTD)**: Modify the `motd` file to change the message displayed to users upon connection.

## Error Handling

The server provides meaningful error messages for invalid commands, authentication failures, and other issues.

## Acknowledgments
- Inspired by the IRC protocol as defined in [RFC 1459](https://tools.ietf.org/html/rfc1459).
- Special thanks to the developers of open-source IRC clients for testing.