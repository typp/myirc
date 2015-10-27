##
## Makefile for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
##
## Made by SiN
## Login   <sin@epitech.net>
##
## Started on  Mon Mar 23 12:25:28 2015 
## Last update Sun Apr 12 23:35:09 2015 
##

CC	= gcc

CFLAGS	= -W -Wall -Wextra -Wno-parentheses

CFLAGS	+= -I ../includes

NAME	= ../client

SRC	= main.c \
	  explode.c \
	  my_implode.c \
	  handshake.c \
	  utils.c \
	  misc.c \
	  command.c

OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all
