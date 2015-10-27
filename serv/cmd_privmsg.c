/*
** c.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 15:40:37 2015 Cyril La Valle
** Last update Sun Apr 12 19:09:49 2015 Cyril La Valle
*/

#include "server.h"

void			privmsg_c(struct s_irc_client *cli,
				  struct s_irc_server *srv,
				  char const *cmd, char const **args)
{
  struct s_irc_chan	*chan;
  struct s_cli_list	*nptr;

  if (arrlen(args) < 2)
    cli_reply(cli, srv, "461 %s PRIVMSG :Not enough parameters", cli->nick);
  else
    {
      if (cli->chan_list)
	{
	  chan = chn_find(cli->chan_list, args[0]);
	  if (chan)
	    for (nptr = chan->clients; nptr; nptr = nptr->next)
	      if (nptr->data && nptr->data->cnx->sockfd != cli->cnx->sockfd)
		cli_reply(nptr->data, srv, ":%s PRIVMSG %s :%s", cli->nick,
			  args[0], args[1]);
	}
    }
}
