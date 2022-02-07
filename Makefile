# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/02/07 11:34:29 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME			= minishell


DIRSRC			= srcs/


DIROBJ			= objs/


# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC				= clang


CFLAGS			= -Wall -Wextra -Werror -g


INCLUDES		= -I ./includes
INCLUDES		+= -I ./libft/includes


LFLAGS			= -Wall -Wextra -Werror -g


LIBRARIES		= -L libft -lft
LIBRARIES		+= -L libft/srcs/print -lprint


# Select the correct path of readline library and includes depending the system

UNAME := $(shell uname -m)

ifeq ($(UNAME), arm64)
	INCLUDES	+= -I /opt/homebrew/opt/readline/include
	LIBRARIES	+= -L /opt/homebrew/opt/readline/lib -lreadline
else
	LIBRARIES	+= -lreadline
endif


# Debug flag, use with 'make DEBUG=1'
ifeq ($(DEBUG), 1)
	CFLAGS		+= -g
	LFLAGS		+= -g
endif


# Optimisation flag, use with 'make OPTI=1'
ifeq ($(OPTI), 1)
	CFLAGS		+= -O2 -O3
	LFLAGS		+= -O2 -O3
endif


# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #


INIT		= init_minishell.c \
			main.c \
			signal.c

PARSING		= env_array_utils.c \
			env_list_utils.c \
			get_command_line.c \
			parse.c \
			parse_command_and_args.c \
			parse_redirections.c \
			parse_simple_commands.c \
			print_structure.c \
			str_and_array_modification.c \
			tokens_count.c \
			tokens_fill.c \
			tokens_get.c

EXPANSION	= expansion.c \
			expansion_env.c \
			expansion_quotes.c \
			expansion_tilde.c \
			command_expansion.c \
			command_split_expansion.c \
			heredoc_expansion.c \
			command_expansion_utils.c \
			expand_env_variable.c \
			redir_expansion.c

BUILTINS	= builtin_cd.c \
			builtin_cd_cdpath.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c

EXECUTION	= execute.c \
			execute_builtin.c \
			execute_simple_command.c \
			execute_with_path.c \
			execute_without_path.c \
			execution.c \
			heredoc.c \
			pipeline.c \
			redirection.c \
			redirection_utils.c

EXIT		= free_minishell.c \
			global_exit_status.c


SRC			= $(addprefix init/, $(INIT)) \
			$(addprefix parsing/, $(PARSING)) \
			$(addprefix expansion/, $(EXPANSION)) \
			$(addprefix execution/, $(EXECUTION)) \
			$(addprefix builtins/, $(BUILTINS)) \
			$(addprefix exit/, $(EXIT))


SRCS		= $(addprefix $(SRC_DIR), $(SRC))


OBJ			:= $(SRC:.c=.o)


DIROBJS		= $(addprefix $(DIROBJ), $(OBJ))


OBJS_DIRECTORIES = objs/init objs/parsing objs/expansion \
				   objs/builtins objs/execution objs/exit



# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #


GREEN		= \033[32;1m
RED			= \033[31;1m
YELLOW		= \033[33;1m
CYAN		= \033[36;1m
RESET		= \033[0m



# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #

.SILENT : all

all : header $(NAME) footer

$(DIROBJ)%.o: $(DIRSRC)%.c
		@mkdir -p $(OBJS_DIRECTORIES)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
$(NAME)	: $(DIROBJS)
		@make --no-print-directory -C libft
		$(CC) $(LFLAGS) $(DIROBJS) $(LIBRARIES) -o $(NAME)
		@printf "\n"

test :	 all
		./minishell

bonus : all

leaks :	all
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=divers/.ignore_readline --track-origins=yes ./minishell

norm :
		@norminette

install: re
		cp $(NAME) ~/bin

clean :
		@make --no-print-directory -C libft clean
		@rm -rf $(DIROBJ)
		@printf "$(RED)"
		@printf "Object files removed\n"
		@printf "$(RESET)"

fclean :
		@make --no-print-directory -C libft fclean
		@-rm -f $(NAME)
		@-rm -rf $(DIROBJ)
		@printf "$(RED)"
		@printf "Binary and object files removed\n"
		@printf "$(RESET)"

re :	divider fclean all

header :
	@printf "$(CYAN)"
	@printf "    __  ________   ___________ __  __________    __ \n"
	@printf "   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n"
	@printf "  / /|_/ // //  |/ // / \__ \/ /_/ / __/ / /   / /  \n"
	@printf " / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n"
	@printf "/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n"
	@printf "\n"
	@printf "MINISHELL COMPILATION\n"
	@printf "$(RESET)"

divider :
	@printf "\n"

footer :
	@printf "$(CYAN)"
	@printf "➤     SUCCESS\n"
	@printf "\nUSAGE\n"
	@printf "$(RESET)"
	@printf "./minishell (for interactive mode)\n"
	@printf "./minishell -c [command] (for non-interactive mode)\n\n"

.PHONY : fclean
