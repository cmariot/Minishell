# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/02/02 15:23:43 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME			= libprint.a
LIBFT			= ../..


# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC				= clang

CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I ./includes
INCLUDES		+= -I ../../includes


# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

DIRSRC		= srcs/

DIROBJ		= objs/

SRC			= print.c \
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

OBJ			:= $(SRC:.c=.o)

DIROBJS		= $(addprefix $(DIROBJ), $(OBJ))

SRCS		= $(addprefix $(SRC_DIR), $(SRC))


# **************************************************************************** #
#                                COLORS                                        #
# **************************************************************************** #

GR		= \033[32;1m
RE		= \033[31;1m
YE		= \033[33;1m
RC		= \033[0m


# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #

all : $(NAME)

$(DIROBJ)%.o: $(DIRSRC)%.c
		@mkdir -p $(DIROBJ)
		@printf "$(YE)"
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
		@printf "$(RC)"
	
$(NAME)	: $(DIROBJS)
		@printf "$(GR)"
		ar rcs $(NAME) $(DIROBJS)
		ranlib $(NAME)
		@printf "$(RC)"

clean :
		@printf "$(RE)"
		rm -rf $(DIROBJ)
		@printf "$(RC)"

fclean :
		@printf "$(RE)"
		rm -f $(NAME)
		rm -rf $(DIROBJ)
		@printf "$(RC)"

re :	 fclean all

.PHONY : clean fclean
