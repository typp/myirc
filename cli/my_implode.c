/*
** my_implode.c for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Sun Apr 12 01:26:24 2015 
** Last update Sun Apr 12 01:35:05 2015 
*/

#include "client.h"

char		*implode(char **w_tab, char sep)
{
  char		*r;
  int		len_total;
  int		i;

  i = -1;
  len_total = 0;
  if (w_tab == NULL)
    return (NULL);
  while (w_tab[++i] != NULL)
    len_total += strlen(w_tab[i]) + 1;
  if ((r = calloc(1, (len_total + 1) * sizeof(char))) == NULL)
    return (NULL);
  i = -1;
  *r = 0;
  while (w_tab[++i] != NULL)
    {
      strcat(r, w_tab[i]);
      if (r != 0)
	r[strlen(r)] = sep;
    }
  r[len_total - 1] = 0;
  return (r);
}
