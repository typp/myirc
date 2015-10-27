/*
** dyntable.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Fri Apr 10 08:46:41 2015 Cyril La Valle
** Last update Sun Apr 12 21:19:57 2015 Cyril La Valle
*/

#include <stdlib.h>
#include <string.h>
#include "vartable.h"

struct s_vartable	*vta_creat(size_t step)
{
  struct s_vartable	*this;

  if (NULL != (this = malloc(sizeof(*this))))
    {
      if (NULL != (this->entries = calloc(step, sizeof(void *))))
	{
	  this->step = step;
	  this->size = step;
	}
      else
	{
	  free(this);
	  this = NULL;
	}
    }
  return (this);
}

void	vta_destroy(struct s_vartable *this)
{
  free(this->entries);
  free(this);
}
