# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/02/01 12:11:43 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME			= libprint.a

SRCS_DIR		= srcs
INCL_DIR		= includes
OBJS_DIR		= objs/

LIBFT			= ../..
LIBFT_INCL		= $(LIBFT)/includes/


# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC			= clang

CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I $(INCL_DIR)
INCLUDES		+= -I $(LIBFT_INCL)

LFLAGS			= -Wall -Wextra -Werror


# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRCS		= print.c \
			  ft_print_char.c \
			  ft_print_str.c \
			  ft_print_integer.c \
			  ft_print_unsigned_int.c \
			  ft_print_addr.c \
			  ft_print_hexa.c \
			  ft_print_upper_hexa.c \
			  ft_print_percent.c \
			  get_flags.c \
			  init_flags.c \
			  print_type.c \
			  ft_space_and_precision.c \
			  ft_star_flag.c

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

create_obj_dir:
		mkdir -p $(OBJS_DIR)

# Compiling
$(OBJS_DIR)%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
$(NAME)	: create_obj_dir $(SRCS) $(OBJS)
		ar rc $(NAME) $(OBJS)

# Remove object files
clean :
		rm -rf $(OBJS_DIR)

# Remove object and binary files
fclean :
		rm -f $(NAME)
		rm -rf $(OBJS_DIR)

# Remove all and recompile
re :	 fclean all

.PHONY : clean fclean
