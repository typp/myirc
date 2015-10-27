/*
** server_cnx.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Mon Apr 06 21:54:12 2015 Cyril La Valle
** Last update Sun Apr 12 21:15:48 2015 Cyril La Valle
*/

#include "server.h"

void			srv_cnx_read(struct s_irc_server *this,
				     struct s_cnx_handle *cnx)
{
  struct s_irc_client	*cli;
  struct sockaddr_in	sin;
  socklen_t		sinlen;
  int			clisockfd;

  if (NULL != (cli = irc_client_creat()))
    {
      sinlen = (socklen_t) sizeof(sin);
      clisockfd = accept(cnx->sockfd, (struct sockaddr *) &sin, &sinlen);
      if (0 <= clisockfd)
	{
	  printf("New client connected\n");
	  cli->family = sin.sin_family;
	  cli->port = sin.sin_port;
	  cli->address = sin.sin_addr.s_addr;
	  cli->cnx->sockfd = clisockfd;
	  cli->command = &cli_command_login;
	  if (-1 == vta_put(this->clients, cli->cnx->sockfd, cli))
	    warn("Cannot append client to server list");
	  return ;
	}
    }
  warn("Cannot accept incoming connexion");
}
