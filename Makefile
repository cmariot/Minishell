# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2021/12/14 12:33:31 by cmariot          ###   ########.fr        #
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
CFLAGS			+= -I $(INCL_DIR)
CFLAGS			+= -I $(LIBFT_INCL)
# Delete the -g3 flag at the end of the project, it's used to have more information w/ valgrind
CFLAGS			+= -g3

LFLAGS			= -Wall -Wextra -Werror -g3
LIB_LFLAGS		= -L $(LIBFT) -lft
LIB_LFLAGS		+= -lreadline


# Debug flag, use with 'make DEBUG=1'
ifeq ($(DEBUG), 1)
	CFLAGS		+= -g3
	LFLAGS		+= -g3
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
			  env.c \
			  setenv.c \
			  unsetenv.c \
			  list_t_env.c \
			  ministruct_utils.c \
			  prompt.c \
			  parse_line.c

SRC			:= $(notdir $(SRCS))

OBJ			:= $(SRC:.c=.o)

OBJS			:= $(addprefix $(OBJS_DIR), $(OBJ))

VPATH			:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)

# **************************************************************************** #
#			   	   COLORS                                      #
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

# Check 42 norm 
norm :
		@norminette

# Remove object files
clean :
		@printf "$(RE)Removing $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n"
		@printf "$(RE)make clean in $(LIBFT) ... "
		@make clean -C $(LIBFT)
		@printf "Done\n"

# Remove object and binary files
fclean :
		@printf "$(RE)Removing $(NAME) ... "
		@rm -f $(NAME)
		@printf "Done\n"
		@printf "$(RE)Removing $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n"
		@make fclean -C $(LIBFT)

print_divider :
		@printf "\n"

# Remove all and recompile
re :	 fclean print_divider all

.PHONY : clean fclean
