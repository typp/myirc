/*
** cmd_quit.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:07:08 2015 Cyril La Valle
** Last update Sun Apr 12 22:47:20 2015 Cyril La Valle
*/

#include "server.h"

void	quit_c(struct s_irc_client *cli,
	       struct s_irc_server *srv,
	       char const *cmd, char const **args)
{
  close(cli->cnx->sockfd);
  cli_disconnect(cli, srv);
}
