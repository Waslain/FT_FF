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
██         ██    ███████ ██ ██   ██  ██████ \n\
\n\
\t\t\t\t\t\tby: Waslain & Manbex\n"

# Path
SRCS_PATH	= ./srcs/
OBJS_PATH	= ./objs/

# Files
SRCS		= main.cpp
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
CFLAGS		= -Wall -Wextra -Werror -std=c++98
#CFLAGS		+= -MMD -g3

# Rules
all		: $(NAME)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "\n\t$(GREEN)$(NAME) created ! 🤖$(RESET)"
	@echo $(BANNER)

leak	: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=./.readline.supp --track-origins=yes ./$(NAME)

exec	: $(NAME) clean
	./$(NAME)

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
$(OBJS_PATH)%.o : $(SRCS_PATH)%.cpp
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -c $< -o $@
		@$(call percentage)
		@printf "$(CLEAR) 🛠️  $(GREEN)[%3d%%]$(RESET) - $(YELLOW)Compiling $< to $@$(RESET)\n" $(PERCENT)

.PHONY : all clean fclean re leak no_env exec

-include $(DEPS)
