# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:07:40 by rmakende          #+#    #+#              #
#    Updated: 2024/12/23 21:15:28 by rmakende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror #-fsanitize=address
#CFLAGS = -Wall -Wextra -Werror


LIBFT_DIR = ./Libft
LIBRARY = $(LIBFT_DIR)/libft.a
LIB_HEADERS = $(LIBFT_DIR)/libft.h

PRINTF_DIR = ./printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
PRINT_HEADERS = $(PRINTF_DIR)/ft_printf.h

SRCS = pipex.c\
	   pipex_utils.c

OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(LIBRARY) $(PRINTF) $(NAME)

$(LIBRARY):
	cd $(LIBFT_DIR) && $(MAKE)

$(PRINTF):
	cd $(PRINTF_DIR) && $(MAKE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY) $(PRINTF)


clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) fclean
	cd $(PRINTF_DIR) && $(MAKE) fclean

fclean: clean
	rm -f $(NAME)
	rm -rf *.txt
	cd $(LIBFT_DIR) && $(MAKE) fclean
	cd $(PRINTF_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
