/*
** array.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 23:10:19 2015 Cyril La Valle
** Last update Sun Apr 12 21:31:39 2015 Cyril La Valle
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

char		**make_str_array(char *first, ...)
{
  va_list	ap;
  va_list	ap_cnt;
  size_t	total;
  size_t	idx;
  char		*sp;
  char		**array;

  if (first == NULL)
    return (calloc(1, sizeof(*array)));
  va_start(ap, first);
  va_copy(ap_cnt, ap);
  total = 0;
  for (sp = first; sp; sp = va_arg(ap_cnt, char *))
    ++total;
  va_end(ap_cnt);
  if (NULL != (array = calloc(total, sizeof(*array))))
    {
      idx = 0;
      for (sp = first; sp; sp = va_arg(ap_cnt, char *))
	array[idx++] = strdup(sp);
    }
  va_end(ap);
  return (array);
}

int		append_to_str_array(char ***arrptr, char *str)
{
  size_t	len;
  char		**ptr;

  parray(*arrptr);
  len = arrlen((char const **) *arrptr);
  if (NULL != (ptr = realloc(*arrptr, (len + 2) * sizeof(**arrptr))))
    {
      ptr[len] = str;
      ptr[len + 1] = NULL;
      *arrptr = ptr;
      return (0);
    }
  return (-1);
}

void		parray(char **array)
{
  size_t	idx;

  if (array == NULL)
    printf("[(nal)]\n");
  else if (array[0] == NULL)
    printf("<array %p []>\n", array);
  else
    {
      printf("<array %p [%s", array, array[0]);
      for (idx = 1; array[idx]; ++idx)
	printf(", %s", array[idx]);
      printf("]>\n");
    }
}

size_t		arrlen(char const **array)
{
  size_t	len;

  len = 0;
  while (array[len])
    ++len;
  return (len);
}
