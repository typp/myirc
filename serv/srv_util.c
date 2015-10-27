/*
** srv_util.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 23:56:50 2015 Cyril La Valle
** Last update Sun Apr 12 21:26:15 2015 Cyril La Valle
*/

#include "server.h"

struct s_irc_client	*srv_find_client_by_nick(struct s_irc_server *this,
						 char const *nick)
{
  struct s_irc_client	*cptr;
  size_t		idx;

  for (idx = 0; idx < this->clients->size; ++idx)
    {
      cptr = vta_get(this->clients, idx);
      if (cptr && strcmp(cptr->nick, nick) == 0)
	return (cptr);
    }
  return (NULL);
}

void			srv_safe_ch_callback(struct s_irc_server *this,
					     size_t cb_off,
					     int fd)
{
  struct s_cnx_handle	*cnx;
  void			(*callback)(struct s_cnx_handle *,
				    struct s_irc_server *);

  cnx = vta_get(this->connexions, fd);
  if (NULL != cnx)
    {
      callback = (void *) ((uintptr_t) cnx + (uintptr_t) cb_off);
      if (NULL != callback)
	callback(cnx, this);
      else
	warnx("Descriptor %i doesn't have callback@+0x%02zX", fd, cb_off);
    }
  else
    warnx("Descriptor %i is not attached to a connexion handler", fd);
}
