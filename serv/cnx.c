/*
** cnx.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Fri Apr 10 12:47:50 2015 Cyril La Valle
** Last update Sun Apr 12 19:41:24 2015 Cyril La Valle
*/

#include "server.h"

struct s_cnx_handle	*cnx_handle_creat(int sockfd)
{
  struct s_cnx_handle	*cnx;

  if (NULL != (cnx = malloc(sizeof(*cnx))))
    {
      if (NULL != (cnx->read_vrb = vrb_creat()))
	{
	  if (NULL != (cnx->write_queue = queue_creat()))
	    {
	      cnx->sockfd = sockfd;
	      return (cnx);
	    }
	  vrb_destroy(cnx->read_vrb);
	}
      free(cnx);
    }
  return (NULL);
}
