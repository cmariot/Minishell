# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/02/02 15:32:12 by cmariot          ###   ########.fr        #
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

CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I ./includes
INCLUDES		+= -I ./libft/includes

LFLAGS			= -Wall -Wextra -Werror

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


INIT		= init/init_minishell.c \
			init/main.c \
			init/signal.c


PARSING		= parsing/env_array_utils.c \
			parsing/env_list_utils.c \
			parsing/get_command_line.c \
			parsing/parse.c \
			parsing/parse_command_and_args.c \
			parsing/parse_redirections.c \
			parsing/parse_simple_commands.c \
			parsing/print_structure.c \
			parsing/str_and_array_modification.c \
			parsing/tokens_count.c \
			parsing/tokens_fill.c \
			parsing/tokens_get.c


EXPANSION	= expansion/expansion.c \
			expansion/expansion_env.c \
			expansion/expansion_quotes.c \
			expansion/expansion_tilde.c \
			expansion/command_expansion.c \
			expansion/command_split_expansion.c \
			expansion/redir_expansion.c



BUILTINS	= builtins/builtin_cd.c \
			builtins/builtin_cd_cdpath.c \
			builtins/builtin_echo.c \
			builtins/builtin_env.c \
			builtins/builtin_exit.c \
			builtins/builtin_export.c \
			builtins/builtin_pwd.c \
			builtins/builtin_unset.c


EXECUTION	= execution/execute.c \
			execution/execute_builtin.c \
			execution/execute_simple_command.c \
			execution/execute_with_path.c \
			execution/execute_without_path.c \
			execution/execution.c \
			execution/heredoc.c \
			execution/pipeline.c \
			execution/redirection.c \
			execution/redirection_utils.c


EXIT		= exit/free_minishell.c \
			exit/global_exit_status.c


SRC			= $(INIT) \
			$(PARSING) \
			$(EXPANSION) \
			$(EXECUTION) \
			$(BUILTINS) \
			$(EXIT)

OBJ			:= $(SRC:.c=.o)

DIROBJS		= $(addprefix $(DIROBJ), $(OBJ))

SRCS		= $(addprefix $(SRC_DIR), $(SRC))

OBJ			:= $(SRC:.c=.o)

OBJS_DIRECTORIES = objs/init objs/parsing objs/expansion objs/builtins objs/execution objs/exit



# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #


GR		= \033[32;1m
RE		= \033[31;1m
YE		= \033[33;1m
CY		= \033[36;1m
RC		= \033[0m



# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #


all : $(NAME)

$(DIROBJ)%.o: $(DIRSRC)%.c
		@mkdir -p $(OBJS_DIRECTORIES)
		@printf "$(YE)"
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
		@printf "$(RC)"
	
$(NAME)	: $(DIROBJS)
		@make -C libft
		@printf "$(GR)"
		$(CC) $(LFLAGS) $(DIROBJS) $(LIBRARIES) -o $(NAME)
		@printf "$(RC)"

test :	 all
		./minishell

norm :
		norminette

clean :
		make -C libft clean
		@printf "$(RE)"
		rm -rf $(DIROBJ)
		@printf "$(RC)"

fclean :
		@make -C libft fclean
		@printf "$(RE)"
		rm -f $(NAME)
		rm -rf $(DIROBJ)
		@printf "$(RC)"

re :	 fclean all

bonus : all

.PHONY : clean fclean
