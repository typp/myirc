/*
** command.c for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Sun Apr 12 02:20:03 2015 
** Last update Sun Apr 12 23:25:23 2015 
*/

#include "client.h"

int		add_channel(t_user *usr, char **tab)
{
  t_channel	*chan;
  t_channel	*buff;

  if ((chan = malloc(sizeof(t_channel))) == NULL)
    return (-1);
  chan->name = tab[1];
  chan->next = NULL;
  buff = usr->srvs->chans;
  if (buff == NULL)
    usr->srvs->chans = chan;
  else
    {
      while (buff->next != NULL)
	buff = buff->next;
      buff->next = chan;
    }
  return (0);
}

int		nick(char **tab, int socket, t_user *user)
{
  char		**tab2;
  char		*tosend;

  if (lentab(tab) - 1 > 2)
    return (printf("not the good number of argument to nick\n"));
  if ((tab2 = malloc(3 * sizeof(char *))) == NULL)
    return (-1);
  tab2[0] = strdup("NICK");
  tab2[1] = strdup(tab[1]);
  tab2[2] = NULL;
  tosend = implode(tab2, ' ');
  user->oldnick = user->nick;
  user->nick = strdup(tab2[1]);
  setwell(tosend, strlen(tosend), socket);
  return (0);
}

int		users(char **tab, int socket, t_user *user)
{
  char		*tosend;
  char		**tab2;

  if (user->current == NULL)
    return (puts("currently not connected to a channel"));
  if ((tab2 = malloc(3 * sizeof(char *))) == NULL)
     return (-1);
  if (lentab(tab) - 1 > 1)
    return (printf("too much argument to users\n"));
  tab2[0] = strdup("NAMES");
  tab2[1] = strdup(user->current);
  tab2[2] = NULL;
  tosend = implode(tab2, ' ');
  setwell(tosend, strlen(tosend), socket);
  return (0);
}

int		join(char **tab, int socket, t_user *user)
{
  char		**tab2;
  char		*tosend;

  if (lentab(tab) - 1 > 2)
    return (printf("not the good number of argument to join\n"));
  if (tab[1][0] != '#')
    return (printf("not a valid channel name\n"));
  if ((tab2 = malloc(3 * sizeof(char *))) == NULL)
    return (-1);
  tab2[0] = strdup("JOIN");
  tab2[1] = strdup(tab[1]);
  tab2[2] = NULL;
  tosend = implode(tab2, ' ');
  setwell(tosend, strlen(tosend), socket);
  add_channel(user, tab2);
  user->current = strdup(tab2[1]);
  return (0);
}

int		list(char **tab, int socket, __attribute__((unused))t_user *user)
{
  char		*tosend;

  if ((tosend = malloc(12 * sizeof(char))) == NULL)
     return (-1);
  if (lentab(tab) - 1 > 1)
    return (printf("too much argument to list\n"));
  tosend = memcpy(tosend, "LIST", 4);
  setwell(tosend, 4, socket);
  return (0);
}
