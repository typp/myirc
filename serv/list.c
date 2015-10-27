/*
** list.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:11:05 2015 Cyril La Valle
** Last update Sun Apr 12 19:57:20 2015 Cyril La Valle
*/

#include <stdlib.h>

#include "list.h"

struct s_list	*list_alloc(void)
{
  struct s_list	*node;

  if (NULL != (node = malloc(sizeof(*node))))
    {
      node->next = NULL;
      node->data = NULL;
    }
  return (node);
}

int		list_add(struct s_list *this, void *data)
{
  struct s_list	*node;

  node = list_alloc();
  node->next = this->next;
  node->data = this->data;
  this->next = node;
  this->data = data;
  return (0);
}
