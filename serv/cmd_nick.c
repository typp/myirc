/*
** cmd_nick.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:06:17 2015 Cyril La Valle
** Last update Sun Apr 12 19:06:28 2015 Cyril La Valle
*/

#include "server.h"

void	nick_c(struct s_irc_client *cli, struct s_irc_server *srv,
	       char const *cmd, char const **args)
{
  if (arrlen(args) < 1)
    cli_reply(cli, srv, "431 :No nickname given");
  else if (strlen(args[0]) != strcspn(args[0], " *\t\b\a\e"))
    cli_reply(cli, srv, "432 %s %s :Erroneous Nickname", cli->nick, args[0]);
  else if (NULL != srv_find_client_by_nick(srv, args[0]))
    cli_reply(cli, srv, "433 %s %s :Nickname is already in use",
	      cli->nick, args[0]);
  else
    strncpy(cli->nick, args[0], sizeof(cli->nick));
}

