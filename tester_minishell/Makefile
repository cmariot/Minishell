# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/01/17 23:40:56 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME			= minishell_tester
SRCS_DIR		= srcs
OBJS_DIR		= objs/
LIBFT			= ../libft
LIBFT_INCL		= $(LIBFT)/includes/


# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC				= clang

CFLAGS			= -Wall -Wextra -Werror
CFLAGS			+= -I $(LIBFT_INCL)
CFLAGS			+= -I ./includes


LFLAGS			= -Wall -Wextra -Werror -g3
LIB_LFLAGS		= -L $(LIBFT) -lft

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
				 tester_utils.c

SRC				:= $(notdir $(SRCS))

OBJ				:= $(SRC:.c=.o)

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
		@mkdir -p log_tests
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(CC) $(CFLAGS) -c $< -o $@\n"
		
# Linking
obj_link :
		@printf "$(YE)$(NAME) compilation success.\n\n"
		@make -C ..
		@printf "$(GR)Linking $(NAME) objects ...\n$(CC) $(LFLAGS) $(OBJS) $(LIB_LFLAGS) -o $(NAME)$(RC)\n"

$(NAME)	: srcs_compil $(SRCS) $(OBJS) obj_link
		@$(CC) $(LFLAGS) $(OBJS) $(LIB_LFLAGS) -o $(NAME)
		@printf "$(GR)Success, $(NAME) is ready.\n\n$(RC)"

leaks : all
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./minishell_tester

# Check 42 norm 
norm :
		@norminette

test : all
		@./minishell_tester

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
		@rm -rf log_tests
		@printf "Done\n"
		@printf "Removing $(NAME) ... "
		@rm -f $(NAME)
		@printf "Done\n$(RC)"

print_divider :
		@printf "\n"

# Remove all and recompile
re :	 fclean print_divider all

.PHONY : clean fclean
