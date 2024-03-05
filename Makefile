##
## EPITECH PROJECT, 2024
## B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
## File description:
## Makefile
##

NAME = myftp

SRC = myftp.c \
		server.c \
		client_utils/client.c \

SRC := $(addprefix src/, $(SRC))

OBJ = $(SRC:.c=.o)

CFLAGS = -W -Wall -Wextra -I./include

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re
