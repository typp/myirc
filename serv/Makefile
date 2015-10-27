##
## Makefile for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
##
## Made by SiN
## Login   <sin@epitech.net>
##
## Started on  Mon Mar 23 12:25:28 2015 SiN
## Last update Sun Apr 12 23:25:32 2015 Cyril La Valle
##

NAME	:= ../server

CC	:= gcc

CFLAGS  := -W -Wall -Wextra -Wno-unused-parameter
CFLAGS  += -I ../includes
LDFLAGS :=

SRC	:=                 \
	   array.c         \
	   branch.c        \
	   chn.c           \
	   cli_cmd_hooks.c \
	   client_cnx.c    \
	   cli_interpret.c \
	   cmd_away.c      \
	   cmd_join.c      \
	   cmd_list.c      \
	   cmd_motd.c      \
	   cmd_names.c     \
	   cmd_nick.c      \
	   cmd_part.c      \
	   cmd_pass.c      \
	   cmd_privmsg.c   \
	   cmd_quit.c      \
	   cmd_user.c      \
	   cnx.c           \
	   explode.c       \
	   init.c          \
	   irc_client.c    \
	   lift.c          \
	   list.c          \
	   main.c          \
	   queue.c         \
	   queue_utils.c   \
	   server_cnx.c    \
	   shutdown.c      \
	   sockaddr.c      \
	   srv_deal.c      \
	   srv_select.c    \
	   srv_util.c      \
	   str2.c          \
	   str.c           \
	   vartable.c      \
	   vartable_util.c \
	   vrb.c           \
	   vrb_get.c       \
	   vrb_into.c      \

OBJ     := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all
