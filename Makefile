# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 19:11:54 by rmakende          #+#    #+#              #
#    Updated: 2024/10/30 18:06:05 by rmakende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# El compilador de C a usar
CC = gcc
# Las flags para el compillador
CFLAGS = -Wall -Wextra -Werror -g3

# Directorios y nombres de librerías
LIBFT_DIR = ./Libft
LIBRARY = $(LIBFT_DIR)/libft.a
LIB_HEADERS = $(LIBFT_DIR)/libft.h

# Archivos del proyecto principal
SRCS = pipex.c

OBJS = $(SRCS:.c=.o)

TARGET = pipex
# Reglas
all: $(LIBRARY) $(PRINTF) $(TARGET)

# Compilar la librería Libft
$(LIBRARY):
	cd $(LIBFT_DIR) && $(MAKE)

# Compilar el proyecto principal y enlazar con las librerías
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBRARY)

# Limpiar archivos objeto y las librerías
clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) clean

# Limpiar todo, incluyendo el ejecutable y las librerías
fclean: clean
	rm -f $(TARGET)
	cd $(LIBFT_DIR) && $(MAKE) fclean

# Recompilar desde cero
re: fclean all

.PHONY: all clean fclean re test
