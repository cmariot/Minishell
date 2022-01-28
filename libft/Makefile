# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/27 18:57:32 by cmariot           #+#    #+#              #
#    Updated: 2022/01/28 10:21:13 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME		= libft.a
SRCS_DIR	= srcs
INCL_DIR	= includes
OBJS_DIR	= objs/

PRINT_DIR	= srcs/print
PRINT_INCL	= srcs/print/includes

# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC		= clang

CFLAGS	= -Wall -Wextra -Werror
CFLAGS	+= -I $(INCL_DIR)
CFLAGS	+= -I $(PRINT_INCL)

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRCS	= colors.c \
		  ft_arraylen.c \
		  ft_atoi.c \
		  ft_atoi_base.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_free_array.c \
		  ft_intlen.c \
		  ft_isadirectory.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_join_array.c \
		  ft_lstadd_back.c \
		  ft_lstadd_front.c \
		  ft_lstclear.c \
		  ft_lstdelone.c \
		  ft_lstiter.c \
		  ft_lstlast.c \
		  ft_lstmap.c \
		  ft_lstnew.c \
		  ft_lstsize.c \
		  ft_memccpy.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putarray.c \
		  ft_putchar.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr.c \
		  ft_putnbr_base.c \
		  ft_putnbr_fd.c \
		  ft_putstack.c \
		  ft_putstr.c \
		  ft_putstr_fd.c \
		  ft_realloc.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strcmp.c \
		  ft_strdup.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtoll.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  get_next_line.c \
		  gnl_without_bn.c

SRC		:= $(notdir $(SRCS))

OBJ		:= $(SRC:.c=.o)

OBJS	:= $(addprefix $(OBJS_DIR), $(OBJ))

VPATH	:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)


# **************************************************************************** #
#                                   COLORS                                     #
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
		@printf "$(YE)Libft compilation ... \n$(RC)"

$(OBJS_DIR)%.o : %.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(YE)$(CC) $(CFLAGS) -c $< -o $@\n$(RC)"

# Linking
obj_link :
		@printf "$(YE)Libft compilation success.\n\n"
		@make -C $(PRINT_DIR)
		@printf "$(GR)Linking Libft objects ...\n"
		@printf "ar rc $(NAME) $(OBJS) $(RC)\n"

$(NAME)	: srcs_compil $(SRCS) $(OBJS) obj_link
		@ar rc $(NAME) $(OBJS)
		@printf "$(GR)Success, $(NAME) is ready.\n\n"

# Check 42 norm
norm :
		@norminette srcs includes

# Remove object files
clean :
		@printf "Removing libft.a $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n"
		@make -C $(PRINT_DIR) clean

# Remove object and binary files
fclean:
		@printf "Removing ${NAME} ... "
		@rm -f ${NAME}
		@printf "Done\n"
		@printf "Removing libft.a $(OBJS_DIR) ... "
		@rm -rf $(OBJS_DIR)
		@printf "Done\n"
		@make -C $(PRINT_DIR) fclean

# Remove all and recompile
re :	 fclean all

.PHONY : clean fclean
