/*
** queue.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 13:09:45 2015 Cyril La Valle
** Last update Sun Apr 12 21:15:28 2015 Cyril La Valle
*/

#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct s_queue		*queue_creat(void)
{
  struct s_queue	*queue;

  if (NULL != (queue = malloc(sizeof(*queue))))
    {
      queue->nodes = NULL;
    }
  return (queue);
}

struct s_queue_node	*queue_node_alloc(void)
{
  struct s_queue_node	*node;

  if (NULL != (node = malloc(sizeof(*node))))
    {
      node->next = NULL;
      node->data = NULL;
    }
  return (node);
}

struct s_queue_node	*queue_node_get_last(struct s_queue_node *nptr)
{
  while (nptr->next)
    nptr = nptr->next;
  return (nptr);
}

void			queue_destroy(struct s_queue *this)
{
  struct s_queue_node	*nptr;

  while (this->nodes)
    {
      nptr = this->nodes;
      this->nodes = nptr->next;
      if (nptr->data)
	free(nptr->data);
      free(nptr);
    }
  free(this);
}
