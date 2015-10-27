/*
** lift.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Mon Apr 06 11:55:12 2015 Cyril La Valle
** Last update Sun Apr 12 22:33:39 2015 Cyril La Valle
*/

#include "server.h"

static int	interrupted;

static void	sigint_handler(int signum)
{
  interrupted = 1;
}

int	srv_lift(struct s_irc_server *this)
{
  interrupted = 0;
  signal(SIGINT, sigint_handler);
  printf("[MyIRC] -- Server ready for connexions !\n");
  while (!interrupted)
    {
      srv_select(this);
      if (!interrupted)
	srv_deal(this);
    }
  return (0);
}
