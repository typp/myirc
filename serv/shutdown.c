/*
** shutdown.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Mon Apr 06 11:56:14 2015 Cyril La Valle
** Last update Sun Apr 12 22:42:47 2015 Cyril La Valle
*/

#include "server.h"

int			srv_shutdown(struct s_irc_server *this)
{
  struct s_irc_client	*cli;
  size_t		idx;

  warnx("Shutdown now");
  if (this)
    {
      for (idx = 0; idx < this->clients->size; ++idx)
	{
	  cli = vta_get(this->clients, idx);
	  if (cli)
	    {
	      warnx("Closing connection over socket %i", cli->cnx->sockfd);
	      close(cli->cnx->sockfd);
	    }
	}
      close(this->sockfd);
    }
  return (0);
}
