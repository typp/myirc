/*
** init.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Mon Apr 06 11:17:16 2015 Cyril La Valle
** Last update Sun Apr 12 21:40:19 2015 Cyril La Valle
*/

#include "server.h"

static int		srv_init_memory(struct s_irc_server **this)
{
  struct s_irc_server	*that;

  if (NULL == (*this = malloc(sizeof(**this))))
    {
      warn("During server memory initialisation");
      return (2);
    }
  that = *this;
  memset(that, 0, sizeof(*that));
  if (NULL == (that->fd_req = malloc(sizeof(*that->fd_req))) ||
      NULL == (that->fd_res = malloc(sizeof(*that->fd_res))) ||
      NULL == (that->connexions = vta_creat(64)) ||
      NULL == (that->clients = vta_creat(255)) ||
      NULL == (that->chan_list = (struct s_chan_list *) list_alloc()))
    {
      warn("During server memory initialisation");
      return (2);
    }
  FD_ZERO(&that->fd_req->read);
  FD_ZERO(&that->fd_req->write);
  FD_ZERO(&that->fd_res->read);
  FD_ZERO(&that->fd_res->write);
  return (0);
}

static int	srv_init_socket(struct s_irc_server *this)
{
  if (0 > (this->sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
      warn("During server initialisation");
      free(this);
      return (3);
    }
  return (0);
}

static int		srv_init_opt(struct s_irc_server *this)
{
  int			on;
  struct s_cnx_handle	*cnx;

  on = 1;
  this->topfd = this->sockfd + 1;
  if (-1 == vta_put(this->connexions,
		    this->sockfd,
		    malloc(sizeof(*this->connexions))) ||
      NULL == (cnx = vta_get(this->connexions, this->sockfd)))
    {
      warn("During server initialisation");
      close(this->sockfd);
      free(this);
      return (2);
    }
  cnx->read_vrb = NULL;
  cnx->write_queue = NULL;
  cnx->sockfd = this->sockfd;
  if (-1 == setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR,
		       &on, sizeof(int)))
    return (4);
  return (0);
}

static int	srv_init_connection(struct s_irc_server *this, int port)
{
  struct sockaddr_in	sin;

  sockaddr_in_set(&sin, AF_INET, htons(port), INADDR_ANY);
  if (0 > bind(this->sockfd, (struct sockaddr *) &sin, sizeof(sin)))
    {
      warn("During server initialisation");
      close(this->sockfd);
      free(this);
      return (5);
    }
  if (0 > listen(this->sockfd, FD_SETSIZE))
    {
      warn("Cannot listen on the socket");
      close(this->sockfd);
      free(this);
      return (6);
    }
  return (0);
}

int	srv_init(struct s_irc_server **this, int argc, char **argv)
{
  int	status;
  int	port;

  port = (argc > 1) ? atoi(argv[1]) : 6667;
  if (0 == (status = srv_init_memory(this)) &&
      0 == (status = srv_init_socket(*this)) &&
      0 == (status = srv_init_opt(*this)) &&
      0 == (status = srv_init_connection(*this, port)))
    return (0);
  return (status);
}
