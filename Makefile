# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2021/12/30 11:25:19 by cmariot          ###   ########.fr        #
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
CFLAGS			+= -I $(INCL_DIR)
CFLAGS			+= -I $(LIBFT_INCL)


LFLAGS			= -Wall -Wextra -Werror -g3
LIB_LFLAGS		= -L $(LIBFT) -lft
LIB_LFLAGS		+= -lreadline

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

SRCS			= main.c \
				builtin.c \
				env_builtin.c \
				env_list_utils.c \
				execute.c \
				expand_env_variable.c \
				get_command_line.c \
				init_minishell.c \
				free_minishell.c \
				parse.c \
				parse_simple_commands.c \
				parse_redirections.c \
				print_structure.c \
				pwd_builtin.c \
				check_quote.c \
				split_command_line.c \
				split_join_heredoc.c \
				split_spaces.c \
				handler.c \
				do_cd.c \

SRC			:= $(notdir $(SRCS))

OBJ			:= $(SRC:.c=.o)

OBJS			:= $(addprefix $(OBJS_DIR), $(OBJ))

VPATH			:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)

# **************************************************************************** #
#							 	   COLORS                                      #
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
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(CC) $(CFLAGS) -c $< -o $@\n"
		
# Linking
obj_link :
		@printf "$(YE)$(NAME) compilation success.\n\n"
		@make -C $(LIBFT)
		@printf "$(GR)Linking $(NAME) objects ...\n$(CC) $(LFLAGS) $(OBJS) $(LIB_LFLAGS) -o $(NAME)$(RC)\n"

$(NAME)	: srcs_compil $(SRCS) $(OBJS) obj_link
		@$(CC) $(LFLAGS) $(OBJS) $(LIB_LFLAGS) -o $(NAME)
		@printf "$(GR)Success, $(NAME) is ready.\n\n$(RC)"

#		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=tests/.ignore_readline --track-origins=yes ./minishell
leaks : all
		valgrind --leak-check=full --show-leak-kinds=all --suppressions=tests/.ignore_readline --track-origins=yes ./minishell

# Check 42 norm 
norm :
		@norminette

# Remove object files
clean :
		@printf "$(RE)make clean in $(LIBFT) ... "
		@make clean -C $(LIBFT)
		@printf "Done\n"
		@printf "Removing $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n$(RC)"

# Remove object and binary files
fclean :
		@printf "$(RE)make fclean in $(LIBFT) ... "
		@make fclean -C $(LIBFT)
		@printf "Done\n"
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
