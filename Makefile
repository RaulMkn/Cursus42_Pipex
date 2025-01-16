# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:07:40 by rmakende          #+#    #+#              #
#    Updated: 2025/01/16 20:12:28 by rmakende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror


LIBFT_DIR = ./Libft
LIBRARY = $(LIBFT_DIR)/libft.a

SRCS = pipex.c\
	   pipex_utils.c

OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(LIBRARY) $(PRINTF) $(NAME)

$(LIBRARY):
	cd $(LIBFT_DIR) && $(MAKE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY)

clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) fclean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
