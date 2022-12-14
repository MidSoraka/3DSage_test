# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 18:25:17 by raho              #+#    #+#              #
#    Updated: 2022/08/10 23:54:12 by vlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doomnukem
SRCS = main.c open_window.c inputs.c mlx_window_loop.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
CC = gcc -Ilibft
CFLAGS = -pthread #-Wall -Werror -Wextra -O2 #-mavx -fsanitize=address -g
UNAME= $(shell uname)
ifeq ($(UNAME), Darwin)
MLXFLAGS = libmlx.dylib
MLIB =  libmlx.dylib
else ifeq ($(UNAME), Linux)
override CFLAGS += -Imlx/Linux
MLXFLAGS =  -Imlx/Linux/ -I/usr/include -I/usr/lib/ mlx/Linux/libmlx.a -lm -lX11 -lXext
MLIB = mlx/Linux/libmlx.a
else
warning:
	@echo "Compilation for platform $(UNAME) not supported."
	exit 1
endif

all:
	@echo "Compiling for platform: $(UNAME)."
	$(MAKE) $(NAME)

$(NAME): $(OBJS) $(MLIB) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLIB) $(MLXFLAGS)

$(LIBFT):
	make -C libft

libmlx.dylib:
	make -C mlx/OS_X
	mv mlx/OS_X/libmlx.dylib libmlx.dylib

mlx/Linux/libmlx.a:
	make -C mlx/Linux

clean	:
	make -C libft clean
	make -C mlx/OS_X clean
	make -C mlx/Linux clean
	rm -f $(OBJS) *~ core *.core

fclean	: clean
	rm -f libmlx.dylib
	rm -rf *.dSYM
	rm -f $(NAME)
	make -C libft fclean

re:	fclean all

.PHONY: all clean fclean re
