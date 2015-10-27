/*
** cmd_user.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:04:40 2015 Cyril La Valle
** Last update Sun Apr 12 23:28:24 2015 Cyril La Valle
*/

#include "server.h"

void	user_c(struct s_irc_client *cli, struct s_irc_server *srv,
	       char const *cmd, char const **args)
{
  if (arrlen(args) < (size_t) 4)
    cli_reply(cli, srv, "461 %s USER :Not enough parameters", cli->nick);
  else
    strncpy(cli->user, args[0], sizeof(cli->user));
}
