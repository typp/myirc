/*
** branch.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 15:11:49 2015 Cyril La Valle
** Last update Sat Apr 11 20:39:16 2015 Cyril La Valle
*/

#include "server.h"

void		*branch(BRANCH_TABLE const *table, char const *symbol)
{
  size_t	idx;

  for (idx = 0; table[idx].name != NULL; ++idx)
    if (strcmp(table[idx].name, symbol) == 0)
      return (table[idx].sptr);
  return (NULL);
}
