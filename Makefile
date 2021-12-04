# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2021/12/04 15:30:08 by cmariot          ###   ########.fr        #
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

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror
CFLAGS			+= -I $(INCL_DIR)
CFLAGS			+= -I $(LIBFT_INCL)

LFLAGS			= -Wall -Wextra -Werror
LIB_LFLAGS		= -L $(LIBFT) -lft
LIB_LFLAGS		+= -lreadline


# Debug flag, use with 'make DEBUG=3'
ifeq ($(DEBUG), 3)
	CFLAGS		+= -g3
	LFLAGS		+= -g3
endif

# Optimisation flag, use with 'make OPTI=3'
ifeq ($(OPTI), 3)
	CFLAGS		+= -O3
	LFLAGS		+= -O3
endif

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRCS			= main.c \
				  get_env.c

SRC				:= $(notdir $(SRCS))

OBJ				:= $(SRC:.c=.o)

OBJS			:= $(addprefix $(OBJS_DIR), $(OBJ))

VPATH			:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)

# **************************************************************************** #
#									COLORS                                     #
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
		@make norm -C $(LIBFT)
		@norminette srcs includes

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
