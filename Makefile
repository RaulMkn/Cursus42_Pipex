# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:07:40 by rmakende          #+#    #+#              #
#    Updated: 2025/05/14 22:03:14 by rmakende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror


LIBFT_DIR = ./Libft
LIBRARY = $(LIBFT_DIR)/libft.a

SRCS = pipex.c\
	   pipex_utils.c

BONUS = pipex_bonus.c\
	   pipex_utils_bonus.c

OBJS = $(SRCS:.c=.o)
BNS = $(BONUS:.c=.o)
NAME = pipex
NAME_BONUS = pipex_bonus

all: $(LIBRARY) $(PRINTF) $(NAME)

$(LIBRARY):
	cd $(LIBFT_DIR) && $(MAKE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY)

bonus: $(LIBRARY) $(PRINTF) $(NAME_BONUS)
$(NAME_BONUS): $(BNS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BNS) $(LIBRARY)

clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) fclean

fclean: clean
	rm -f $(NAME)
	rm -rf $(BNS)
	cd $(LIBFT_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
