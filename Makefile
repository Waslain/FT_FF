NAME		= ircserv

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
RESET		= \033[0m

# Header

BANNER = "\n\
███████ ████████         ██ ██████   ██████ \n\
██         ██            ██ ██   ██ ██      \n\
█████      ██            ██ ██████  ██      \n\
██         ██            ██ ██   ██ ██      \n\
██         ██            ██ ██   ██  ██████ \n\
\t\t\t\b\b\b\b\b\b\b███████\n\
\n\
\t\t\t\t\t\tby: Waslain & Manbex\n"

# Path
INCL_PATH	= ./incl/
SRCS_PATH	= ./srcs/
OBJS_PATH	= ./objs/

# Files
INCL		=	Server.hpp			\
				User.hpp			\
				Channel.hpp			\
				colors.hpp
SRCS		=	main.cpp			\
				Server.cpp			\
				User.cpp			\
				Channel.cpp			\
				socket.cpp			\
				loop.cpp			\
				handleEvents.cpp	\
				parse.cpp			\
				message.cpp			\
				register.cpp		\
				utils.cpp			\
				$(addprefix cmd/,	\
				PASS.cpp			\
				CAP.cpp				\
				NICK.cpp			\
				USER.cpp			\
				PING.cpp			\
				QUIT.cpp			\
				LUSERS.cpp			\
				VERSION.cpp			\
				MOTD.cpp			\
				JOIN.cpp			\
				PART.cpp			\
				PRIVMSG.cpp			\
				NAMES.cpp			\
				TOPIC.cpp			\
				MODE.cpp			\
				KICK.cpp			\
				INVITE.cpp			\
				)
INCL		:= $(addprefix $(INCL_PATH), $(INCL))
SRCS		:= $(addprefix $(SRCS_PATH), $(SRCS))
OBJS		:= $(subst $(SRCS_PATH), $(OBJS_PATH), $(SRCS:.cpp=.o))
DEPS		:= $(OBJS:.o=.d)

# Variables
CLEAR		= \e[0K
NB_FILES	= $(words $(SRCS))
INDEX		= 0
PERCENT		= 0
define percentage
	$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB_FILES)))))
endef

# Compilator
CC			= c++
CFLAGS		= -I $(INCL_PATH) -Wall -Wextra -Werror -std=c++98 -D DEBUG=$(DEBUG) -g3
CDEBUGFLAGS		= -g3 -D DEBUG=1


# Rules
all	: DEBUG = 0
all		: $(NAME)

bonus	: all

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "\n\t$(GREEN)$(NAME) created ! 🤖$(RESET)"
	@echo $(BANNER)

leak	: DEBUG = 0
leak	: fclean $(NAME) clean
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 8080 pass

debug	: DEBUG = 1
debug	: fclean $(NAME) clean
	./$(NAME) 8080 pass
	
exec	: DEBUG = 0
exec	: fclean $(NAME) clean
	./$(NAME) 8080 pass

no_env	: $(NAME)
	@env -i ./$(NAME)

clean	:
	@rm -rf $(OBJS_PATH) $(OBJS) $(DEPS)
	@echo "Objects deleted 🗑️"

fclean	: clean
	@rm -rf $(NAME)
	@echo "Executable deleted 🗑️"

re		: fclean all

# Rules for .o files
$(OBJS_PATH)%.o : $(SRCS_PATH)%.cpp $(INCL)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -c $< -o $@
		@$(call percentage)
		@printf "$(CLEAR) 🛠️  $(GREEN)[%3d%%]$(RESET) - $(YELLOW)Compiling $< to $@$(RESET)\n" $(PERCENT)

.PHONY : all clean fclean re leak no_env exec

-include $(DEPS)
