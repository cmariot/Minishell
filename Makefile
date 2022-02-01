# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/02/01 13:33:55 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME			= minishell

SRCS_DIR		= srcs
INCL_DIR		= includes
OBJS_DIR		= objs/

LIBFT			= libft
LIBFT_INCL		= $(LIBFT)/includes/


# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC			= clang

CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I $(INCL_DIR)
INCLUDES		+= -I $(LIBFT_INCL)

LFLAGS			= -Wall -Wextra -Werror

LIBRARIES		= -L $(LIBFT) -lft
LIBRARIES		+= -L $(LIBFT)/srcs/print -lprint


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


SRCS		= $(INIT) \
		$(PARSING) \
		$(EXPANSION) \
		$(EXECUTION) \
		$(BUILTINS) \
		$(EXIT)


SRC		:= $(notdir $(SRCS))


OBJ		:= $(SRC:.c=.o)


OBJS		:= $(addprefix $(OBJS_DIR), $(OBJ))


VPATH		:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)


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

create_objs_dir:
		mkdir -p $(OBJS_DIR)

# Compiling
$(OBJS_DIR)%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
	
# Linking
obj_link :
		make -C $(LIBFT)

$(NAME)	: create_objs_dir $(SRCS) $(OBJS) obj_link
		$(CC) $(LFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)


# Compile and launch
test : all
		./minishell


# Check 42 norm 
norm :
		norminette


bonus : all


# Remove object files
clean :
		make clean -C $(LIBFT)
		rm -rf $(OBJS_DIR)


# Remove object and binary files
fclean :
		rm -rf $(OBJS_DIR)
		rm -f $(NAME)
		make fclean -C $(LIBFT)


# Remove all and recompile
re :	 fclean all


.PHONY : clean fclean
