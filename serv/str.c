/*
** str.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 22:46:40 2015 Cyril La Valle
** Last update Sun Apr 12 21:18:26 2015 Cyril La Valle
*/

#include "server.h"

int	strcut(char **dest, char *src, int c)
{
  while (*src)
    {
      if (*src == c)
	{
	  *src = 0;
	  *dest = src + 1;
	  return (0);
	}
      ++src;
    }
  *dest = src;
  return (-1);
}

int	strscut(char **dest, char *src, char *needle)
{
  *dest = strstr(src, needle);
  if (*dest != NULL)
    {
      **dest = '\0';
      *dest += strlen(needle);
    }
  return (0);
}

char	*strlchr(char *str, int chr)
{
  char	*ret;

  ret = strchr(str, chr);
  if (ret != NULL)
    while (*ret && *(ret + 1) == chr)
      ++ret;
  return (ret);
}
