/*
** cmd_join.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:02:53 2015 Cyril La Valle
** Last update Sun Apr 12 21:43:50 2015 Cyril La Valle
*/

#include "server.h"

void			join_c(struct s_irc_client *cli,
			       struct s_irc_server *srv,
			       char const *cmd, char const **args)
{
  struct s_irc_chan	*chan;

  if (arrlen(args) < 1)
    cli_reply(cli, srv, "461 %s JOIN :Not enough parameters", cli->nick);
  else if (NULL != (chan = chn_find_or_create(srv->chan_list, args[0])))
    {
      if (0 > chn_join(chan, cli, srv))
	{
	  warn("Cannot let user '%s' join channel '%s'",
	       cli->nick, chan->name);
	  cli_reply(cli, srv, "500 %s :Internal server error", cli->nick);
	}
      else
	{
	  cli_reply(cli, srv, "332 %s %s :%s", cli->nick,
		    chan->name, chan->topic);
	}
    }
  else
    {
      warn("Cannot let user '%s' join channel '%s'", cli->nick, chan->name);
      cli_reply(cli, srv, "500 %s :Internal server error", cli->nick);
    }
}
