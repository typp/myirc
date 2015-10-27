/*
** cmd_part.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:06:43 2015 Cyril La Valle
** Last update Sun Apr 12 22:13:45 2015 Cyril La Valle
*/

#include "server.h"

void			cli_part(struct s_irc_client *cli,
				 struct s_irc_chan *chan)
{
  struct s_chan_list	*nptr;
  struct s_chan_list	*fr;

  for (nptr = cli->chan_list; nptr; nptr = nptr->next)
    {
      if (nptr->data && strcmp(nptr->data->name, chan->name) == 0)
	{
	  cli->chan_list = nptr->next;
	  free(nptr);
	  return ;
	}
      else if (nptr->next && nptr->next->data &&
	       strcmp(nptr->next->data->name, chan->name) == 0)
	{
	  fr = nptr->next;
	  nptr->next = nptr->next->next;
	  free(fr);
	  return ;
	}
    }
}

void			part_c(struct s_irc_client *cli,
			       struct s_irc_server *srv,
			       char const *cmd, char const **args)
{
  struct s_irc_chan	*chan;

  if (arrlen(args) < 1)
    cli_reply(cli, srv, "461 %s PART :Not enough parameters",
	      cli->nick);
  else if (NULL != (chan = chn_find(cli->chan_list, args[0])))
    {
      chn_part(chan, cli, srv);
      cli_part(cli, chan);
    }
  else
    cli_reply(cli, srv, "442 %s %s :You're not on that channel",
	      cli->nick, args[0]);
}
