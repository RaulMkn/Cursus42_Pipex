# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:07:40 by rmakende          #+#    #+#              #
#    Updated: 2024/12/03 21:57:57 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR = ./Libft
LIBRARY = $(LIBFT_DIR)/libft.a
LIB_HEADERS = $(LIBFT_DIR)/libft.h

PRINTF_DIR = ./printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
PRINT_HEADERS = $(PRINTF_DIR)/ft_printf.h

SRCS = pipex.c\
	   pipex_utils.c

OBJS = $(SRCS:.c=.o)
TARGET = pipex

all: $(LIBRARY) $(PRINTF) $(TARGET)

$(LIBRARY):
	cd $(LIBFT_DIR) && $(MAKE)

$(PRINTF):
	cd $(PRINTF_DIR) && $(MAKE)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBRARY) $(PRINTF)

clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) clean
	cd $(PRINTF_DIR) && $(MAKE) clean

fclean: clean
	rm -f $(TARGET)
	cd $(LIBFT_DIR) && $(MAKE) fclean
	cd $(PRINTF_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
