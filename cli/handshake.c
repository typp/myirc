/*
** handshake.c for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Sun Apr 12 02:19:41 2015 
** Last update Sun Apr 12 19:48:34 2015 
*/

#include "client.h"

int			do_handshake(t_user *user, int sock)
{
  struct passwd		*passwd;

  if ((user->host = malloc((HOST_NAME_MAX + 1) * sizeof(char))) == NULL)
    return (-1);
  passwd = getpwuid(getuid());
  user->real = strdup(passwd->pw_gecos);
  if (!strlen(user->real))
    user->real = strdup("*");
  user->nick = strndup(passwd->pw_name, 9);
  if (!strlen(user->nick))
    user->nick = strdup("*");
  gethostname(user->host, HOST_NAME_MAX);
  if (!strlen(user->host))
    user->host = strdup("*");
  nick_hdsh(user, sock);
  user_hdsh(user, sock);
  return (1);
}

int			nick_hdsh(t_user *user, int sock)
{
  char			*tosend;

  if ((tosend = malloc(strlen(user->nick) + 6 + 2)) == NULL)
    return (-1);
  memcpy(tosend, "NICK ", 5);
  memcpy(tosend + 5, user->nick, strlen(user->nick));
  setwell(tosend, strlen(user->nick) + 5, sock);
  return (0);
}

int			user_hdsh(t_user *user, int socket)
{
  char			**tab;
  char			*tosend;

  if ((tab = malloc(6 * sizeof(char *))) == NULL)
     return (-1);
  tab[0] = strdup("USER");
  tab[1] = strdup(user->nick);
  tab[2] = strdup(user->host);
  tab[3] = strdup(user->srvs->srvname);
  tab[4] = strdup(user->real);
  tab[5] = NULL;
  tosend = implode(tab, ' ');
  setwell(tosend, strlen(tosend), socket);
  return (0);
}
