/*
** queue_utils.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 21:14:32 2015 Cyril La Valle
** Last update Sun Apr 12 21:15:15 2015 Cyril La Valle
*/

#include <stdlib.h>
#include <string.h>
#include "queue.h"

int			queue_push(struct s_queue *this, char const *data)
{
  struct s_queue_node	**pptr;

  if (this->nodes)
    pptr = &queue_node_get_last(this->nodes)->next;
  else
    pptr = &this->nodes;
  if (NULL != (*pptr = queue_node_alloc()))
    {
      if (NULL != ((*pptr)->data = strdup(data)))
	{
	  return (0);
	}
      free(*pptr);
      *pptr = NULL;
    }
  return (-1);
}

char	*queue_front(struct s_queue *this)
{
  if (this->nodes)
    return (this->nodes->data);
  return (NULL);
}

void			queue_pop(struct s_queue *this)
{
  struct s_queue_node	*nptr;

  if (this->nodes)
    {
      nptr = this->nodes;
      this->nodes = nptr->next;
      if (nptr->data)
	free(nptr->data);
      free(nptr);
    }
}

int	queue_is_empty(struct s_queue *this)
{
  return (NULL == this->nodes);
}
