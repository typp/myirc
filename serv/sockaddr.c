/*
** sockaddr.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Mon Apr 06 11:45:16 2015 Cyril La Valle
** Last update Sun Apr 12 21:16:54 2015 Cyril La Valle
*/

#include <netinet/in.h>
#include <string.h>

void	sockaddr_in_set(struct sockaddr_in *sin,
			sa_family_t family,
			in_port_t port,
			in_addr_t addr)
{
  memset(sin, 0, sizeof(*sin));
  sin->sin_family = family;
  sin->sin_port = port;
  sin->sin_addr.s_addr = addr;
}
