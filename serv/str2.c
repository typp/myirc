/*
** str2.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 21:17:47 2015 Cyril La Valle
** Last update Sun Apr 12 21:29:17 2015 Cyril La Valle
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include "str.h"

char	*strupper(char *str)
{
  char	*sp;

  sp = str;
  while (*sp)
    {
      if (islower(*sp))
	*sp = toupper(*sp);
      ++sp;
    }
  return (str);
}

ssize_t		stralcat(char **buffer, char const *s1, char const *s2)
{
  size_t	len;
  char		*mem;

  len = strlen(s1) + strlen(s2);
  if (NULL != (mem = malloc(len)))
    {
      strcpy(mem, s1);
      strcat(mem, s2);
      *buffer = mem;
    }
  else
    return ((ssize_t) -1);
  return ((ssize_t) len);
}
