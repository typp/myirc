/*
** srv_select.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 22:27:51 2015 Cyril La Valle
** Last update Sun Apr 12 22:39:09 2015 Cyril La Valle
*/

#include "server.h"

void			srv_select_set_clients(struct s_irc_server *this)
{
  struct s_irc_client	*cli;
  size_t		idx;

  for (idx = 0; idx < this->clients->size; ++idx)
    {
      cli = vta_get(this->clients, idx);
      if (cli)
	{
	  if (queue_is_empty(cli->cnx->write_queue))
	    FD_SET(cli->cnx->sockfd, &this->fd_req->read);
	  else
	    FD_SET(cli->cnx->sockfd, &this->fd_req->write);
	  if (this->topfd < cli->cnx->sockfd)
	    this->topfd = cli->cnx->sockfd;
	}
    }
}

void	srv_select(struct s_irc_server *this)
{
  srv_select_set_clients(this);
  FD_SET(this->sockfd, &this->fd_req->read);
  if (this->topfd < this->sockfd)
    this->topfd = this->sockfd;
  ++this->topfd;
  if (-1 == select(this->topfd,
		   &this->fd_req->read,
		   &this->fd_req->write,
		   NULL,
		   NULL))
    warn("select");
}
