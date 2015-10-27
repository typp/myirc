/*
** cmd_list.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:03:24 2015 Cyril La Valle
** Last update Sun Apr 12 19:03:40 2015 Cyril La Valle
*/

#include "server.h"

void			list_c(struct s_irc_client *cli, struct s_irc_server *srv,
			       char const *cmd, char const **args)
{
  struct s_chan_list	*chan;

  cli_reply(cli, srv, "321 Channel :Users Name");
  if (srv->chan_list)
    for (chan = srv->chan_list; chan->next; chan = chan->next)
      cli_reply(cli, srv, "322 %s :%s",
		chan->data->name, chan->data->topic);
  cli_reply(cli, srv, "323 :End of /LIST");
}
