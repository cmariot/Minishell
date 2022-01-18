# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/01/18 15:20:26 by cmariot          ###   ########.fr        #
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

CC				= clang

CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I $(INCL_DIR)
INCLUDES		+= -I $(LIBFT_INCL)

LFLAGS			= -Wall -Wextra -Werror

LIBRARIES		= -L $(LIBFT) -lft

# Select the correct path of readline library and includes depending the system
UNAME := $(shell uname -m)
ifeq ($(UNAME), arm64)
	INCLUDES		+= -I /opt/homebrew/opt/readline/include
	LIBRARIES		+= -L /opt/homebrew/opt/readline/lib -lreadline
else
	LIBRARIES		+= -lreadline
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

BUILTINS	= builtins/builtin_cd.c \
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

EXPANSION	= expansion/expansion.c \
			  expansion/expansion_env.c \
			  expansion/expansion_quotes.c \
			  expansion/expansion_tilde.c

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

SRCS		= $(INIT) \
			  $(PARSING) \
			  $(EXPANSION) \
			  $(EXECUTION) \
			  $(BUILTINS) \
			  $(EXIT)

SRC			:= $(notdir $(SRCS))

OBJ			:= $(SRC:.c=.o)

OBJS			:= $(addprefix $(OBJS_DIR), $(OBJ))

VPATH			:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)


# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m


# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #

all : $(NAME)

# Compiling
srcs_compil :
		@printf "$(YE)Source code compilation ... \n"

$(OBJS_DIR)%.o : %.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
		@printf "$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@\n"
		
# Linking
obj_link :
		@printf "$(YE)$(NAME) compilation success.\n\n"
		@make -C $(LIBFT)
		@printf "$(GR)Linking $(NAME) objects ...\n"
		@printf "$(CC) $(LFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)$(RC)\n"

$(NAME)	: srcs_compil $(SRCS) $(OBJS) obj_link
		@$(CC) $(LFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)
		@printf "$(GR)Success, $(NAME) is ready.\n\n$(RC)"

# Compile and launch
test : all
		@./minishell

#Check the leaks with valgrind and some useful flags
leaks : all
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=divers/.ignore_readline --track-origins=yes ./minishell

# Check 42 norm 
norm :
		@norminette

bonus : all

# Remove object files
clean :
		@printf "$(RE)make clean in $(LIBFT) ... \n"
		@make clean -C $(LIBFT)
		@printf "Done\n\n"
		@printf "Removing $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n$(RC)"

# Remove object and binary files
fclean :
		@printf "$(RE)make fclean in $(LIBFT) ... \n"
		@make fclean -C $(LIBFT)
		@printf "Done\n\n"
		@printf "Removing $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n"
		@printf "Removing $(NAME) ... "
		@rm -f $(NAME)
		@printf "Done\n$(RC)"

print_divider :
		@printf "\n"

# Remove all and recompile
re :	 fclean print_divider all

.PHONY : clean fclean
