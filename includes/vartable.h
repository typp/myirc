/*
** vartable.h for includes in /home/la-val_c/rendu/PSU/myirc/includes
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Fri Apr 10 09:23:28 2015 Cyril La Valle
** Last update Sun Apr 12 21:08:59 2015 Cyril La Valle
*/

#include <stddef.h>

struct		s_vartable
{
  size_t	size;
  size_t	step;
  void		**entries;
};

typedef struct s_vartable t_vartable;

t_vartable *vta_creat(size_t step);
size_t     vta_get_count(t_vartable *this);
int        vta_put(t_vartable *this, size_t index, void *entry);
int        vta_put_back(struct s_vartable *this, void *entry);
void       *vta_get(t_vartable *this, size_t index);
void       vta_destroy(t_vartable *this);
