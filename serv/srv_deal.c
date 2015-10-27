/*
** srv_deal.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 22:28:33 2015 Cyril La Valle
** Last update Sun Apr 12 22:28:53 2015 Cyril La Valle
*/

#include "server.h"

void	srv_fdset_flip(struct s_irc_server *this)
{
  void	*fd_res;

  fd_res = this->fd_res;
  this->fd_req = this->fd_res;
  this->fd_res = fd_res;
}

void			srv_deal(struct s_irc_server *this)
{
  int			fd;
  struct s_irc_client	*cliptr;
  struct s_cnx_handle	*srv_cnx;

  srv_fdset_flip(this);
  for (fd = 0; fd < this->topfd; ++fd)
    {
      cliptr = vta_get(this->clients, fd);
      if (FD_ISSET(fd, &this->fd_res->read))
	{
	  if (NULL != cliptr)
	    cli_cnx_read(cliptr, this);
	  else if (NULL != (srv_cnx = vta_get(this->connexions, fd)))
	    srv_cnx_read(this, srv_cnx);
	}
      else if (FD_ISSET(fd, &this->fd_res->write) && NULL != cliptr)
	cli_cnx_write(cliptr, this);
    }
  FD_ZERO(&this->fd_res->read);
  FD_ZERO(&this->fd_res->write);
}

