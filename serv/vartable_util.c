/*
** vartable_util.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 21:19:17 2015 Cyril La Valle
** Last update Sun Apr 12 21:19:56 2015 Cyril La Valle
*/

#include <stdlib.h>
#include <string.h>
#include "vartable.h"

static int	vta_extend_to(struct s_vartable *this, size_t index)
{
  void		**new_mem;
  size_t	size;

  size = index + (this->step - index % this->step);
  if (NULL != (new_mem = realloc(this->entries, size * sizeof(void *))))
    {
      this->entries = new_mem;
      memset(this->entries + this->size, 0,
	     size * sizeof(void *) - this->size * sizeof(void *));
      this->size = size;
      return (0);
    }
  return (-1);
}

int	vta_put(struct s_vartable *this, size_t index, void *entry)
{
  if (index < this->size || 0 == vta_extend_to(this, index))
    this->entries[index] = entry;
  else
    return (-1);
  return (0);
}

int		vta_put_back(struct s_vartable *this, void *entry)
{
  size_t	idx;

  idx = 0;
  while (idx < this->size && this->entries[idx])
    ++idx;
  return (vta_put(this, idx, entry));
}

void	*vta_get(struct s_vartable *this, size_t index)
{
  if (index >= this->size)
    return (NULL);
  return (this->entries[index]);
}
