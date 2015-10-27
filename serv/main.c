/*
** main.c for MyIRC in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Mon Mar 23 12:26:19 2015 SiN
** Last update Sun Apr 12 21:37:51 2015 Cyril La Valle
*/

#include "server.h"

int			main(int argc, char **argv)
{
  int			rt;
  struct s_irc_server	*irc_server;

  if (0 == (rt = srv_init(&irc_server, argc, argv)) &&
      0 == (rt = srv_lift(irc_server)) &&
      0 == (rt = srv_shutdown(irc_server)))
    return (EXIT_SUCCESS);
  else
    warnx("Unable to initialize server, aborting now.");
  return (rt);
}
