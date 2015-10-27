/*
** client_cnx.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Thu Apr 09 17:51:07 2015 Cyril La Valle
** Last update Sun Apr 12 23:30:33 2015 Cyril La Valle
*/

#include "server.h"

void		cli_cnx_read(struct s_irc_client *this,
			     struct s_irc_server *server)
{
  ssize_t	code;

  code = vrb_socket_recv(this->cnx->sockfd, this->cnx->read_vrb, 0);
  if (code > 0)
    {
      cli_interpret_command(this, server);
    }
  else if (code < 0)
    {
      warn("Cannot read over descriptor %i", this->cnx->sockfd);
    }
  else
    {
      warnx("Connexion on descriptor %i lost", this->cnx->sockfd);
      cli_disconnect(this, server);
    }
}

void		cli_reply(struct s_irc_client *this,
			  struct s_irc_server *srv,
			  char const *fmt, ...)
{
  char		*buffer;
  ssize_t	rt;
  va_list	ap;

  va_start(ap, fmt);
  rt = vasprintf(&buffer, fmt, ap);
  va_end(ap);
  if (rt > 0)
    {
      if (NULL != (buffer = realloc(buffer, strlen(buffer) + 3)))
	{
	  strcat(buffer, "\r\n");
	  rt = queue_push(this->cnx->write_queue, buffer);
	  free(buffer);
	  if (rt >= 0)
	    return ;
	}
    }
  warn("Cannot build reply");
}

ssize_t		cli_queue_send(struct s_irc_client *this)
{
  char		*msg;
  ssize_t	ret;

  msg = queue_front(this->cnx->write_queue);
  if (msg)
    ret = send(this->cnx->sockfd, msg, strlen(msg), 0);
  else
    {
      errno = EFAULT;
      ret = -1;
    }
  return (ret);
}

void		cli_cnx_write(struct s_irc_client *this,
			      struct s_irc_server *srv)
{
  ssize_t	code;

  code = cli_queue_send(this);
  if (code > 0)
    {
      queue_pop(this->cnx->write_queue);
    }
  else if (code < 0)
    {
      warn("Cannot write over descriptor %i", this->cnx->sockfd);
      if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR)
	cli_disconnect(this, srv);
    }
  else
    {
      warnx("Descriptor %i unavailable", this->cnx->sockfd);
    }
}

void	cli_disconnect(struct s_irc_client *this,
		       struct s_irc_server *srv)
{
  printf("Client disconnected\n");
  vta_put(srv->clients, this->cnx->sockfd, NULL);
}
