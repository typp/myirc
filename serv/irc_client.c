/*
** irc_client.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Fri Apr 10 12:42:53 2015 Cyril La Valle
** Last update Sun Apr 12 17:10:21 2015 Cyril La Valle
*/

#include "server.h"

struct s_irc_client	*irc_client_creat(void)
{
  struct s_irc_client	*cli;

  if (NULL != (cli = malloc(sizeof(*cli))))
    {
      memset(cli, 0, sizeof(*cli));
      if (NULL == (cli->cnx = cnx_handle_creat(-1)) ||
	  NULL == (cli->chan_list = (struct s_chan_list *) list_alloc()))
	{
	  free(cli);
	  cli = NULL;
	}
    }
  return (cli);
}
