/*
** chn.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 22:16:41 2015 Cyril La Valle
** Last update Sun Apr 12 22:11:01 2015 Cyril La Valle
*/

#include "server.h"

struct s_irc_chan	*chn_creat(char const *name)
{
  struct s_irc_chan	*chan;

  if (NULL != (chan = malloc(sizeof(*chan))))
    {
      memset(chan, 0, sizeof(*chan));
      if (NULL == (chan->clients = (struct s_cli_list *) list_alloc()))
	{
	  free(chan);
	  chan = NULL;
	}
      else
	{
	  strncpy(chan->name, name, sizeof(chan->name));
	  chan->topic = strdup("");
	}
    }
  return (chan);
}

struct s_irc_chan	*chn_find_or_create(struct s_chan_list *list,
					    char const *name)
{
  struct s_chan_list	*nptr;

  for (nptr = list; nptr->next != NULL; nptr = nptr->next)
    if (nptr->data && strcmp(nptr->data->name, name) == 0)
      return (nptr->data);
  if (NULL != (nptr->next = (struct s_chan_list *) list_alloc()))
    {
      if (NULL != (nptr->data = chn_creat(name)))
	{
	  return (nptr->data);
	}
      free(nptr->next);
    }
  return (NULL);
}

struct s_irc_chan	*chn_find(struct s_chan_list *list, char const *name)
{
  struct s_chan_list	*nptr;

  for (nptr = list; nptr->next != NULL; ++nptr)
    if (nptr->data && strcmp(nptr->data->name, name) == 0)
      return (nptr->data);
  return (NULL);
}

int	chn_join(struct s_irc_chan *chan, struct s_irc_client *cli,
		 struct s_irc_server *srv)
{
  list_add((struct s_list *) chan->clients, cli);
  list_add((struct s_list *) cli->chan_list, chan);
  return (0);
}

void			chn_part(struct s_irc_chan *chan,
				 struct s_irc_client *cli,
				 struct s_irc_server *srv)
{
  struct s_cli_list	*nptr;
  struct s_cli_list	*fr;

  for (nptr = chan->clients; nptr; nptr = nptr->next)
    {
      if (nptr->data && strcmp(nptr->data->nick, cli->nick) == 0)
	{
	  chan->clients = nptr->next;
	  free(nptr);
	  return ;
	}
      else if (nptr->next && nptr->next->data &&
	       strcmp(nptr->next->data->nick, cli->nick) == 0)
	{
	  fr = nptr->next;
	  nptr->next = nptr->next->next;
	  free(fr);
	  return ;
	}
    }
  for (nptr = chan->clients; nptr; nptr = nptr->next)
    if (nptr->data)
      cli_reply(cli, srv, ":%s PART %s", cli->nick, chan->name);
}
