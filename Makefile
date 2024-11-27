# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fileonar <fileonar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 18:52:22 by fileonar          #+#    #+#              #
#    Updated: 2024/11/27 13:29:30 by fileonar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = client.c server.c

CLIENT_NAME = client
SERVER_NAME = server

CLIENT_OBJS = $(CLIENT_SRCS:%.c=bin/%.o)
SERVER_OBJS = $(SERVER_SRCS:%.c=bin/%.o)

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

LIB = -L./libft -lft
HEADER = -I./libft 

DEPS = minitalk.h

ifeq ($(DEBUG), 1)
CFLAGS += -g3
debug: re
endif

all: $(CLIENT_NAME) $(SERVER_NAME)

bin:
	@mkdir -p bin

bin/%.o : %.c $(DEPS) | bin
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADER)

./libft/libft.a:
	@git submodule update --init ./libft
	@make -C ./libft

$(CLIENT_NAME):  $(CLIENT_OBJS) ./libft/libft.a
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(LIB) $(HEADER) $(CFLAGS)

$(SERVER_NAME):  $(SERVER_OBJS) ./libft/libft.a
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) $(LIB) $(HEADER) $(CFLAGS)

clean:
	@rm -rf bin
	@echo "cleaned"

fclean: clean
	@rm -f $(CLIENT_NAME) $(SERVER_NAME)
	@echo "fcleaned"

re: fclean all

.PHONY: all clean fclean re