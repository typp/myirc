/*
** cmd_motd.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:03:53 2015 Cyril La Valle
** Last update Sun Apr 12 23:22:56 2015 Cyril La Valle
*/

#include "server.h"

void			names_c(struct s_irc_client *cli,
				struct s_irc_server *srv,
				char const *cmd, char const **args)
{
  struct s_irc_chan	*chan;
  struct s_cli_list	*nptr;
  char			*names;
  size_t		len;

  if (arrlen(args) < 1)
    cli_reply(cli, srv, "461 %s NAMES :Not enough parameters", cli->nick);
  if (NULL != (chan = chn_find(srv->chan_list, args[0])))
    {
      len = 0;
      if (NULL != (names = calloc(1, 1)))
	{
	  for (nptr = chan->clients; nptr; nptr = nptr->next)
	    if (nptr->data)
	      {
		len += strlen(nptr->data->nick) + 2;
		if (NULL != (names = realloc(names, len)))
		  strcat(strcat(names, nptr->data->nick), " ");
		else
		  return ;
	      }
	  cli_reply(cli, srv, "353 %s %s :%s", cli->nick, args[0], names);
	  cli_reply(cli, srv, "366 %s :End of /NAMES list", cli->nick);
	}
    }
}
