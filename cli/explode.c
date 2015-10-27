/*
** my_str_to_wordtab.c for  in /home/ravane_a/rendu/PSU_2013_minishell1
**
** Made by
** Login   <ravane_a@epitech.net>
**
** Started on  Mon Dec 16 19:15:34 2013
** Last update Thu Apr  9 23:30:25 2015 
*/

#include "client.h"

char		*strnncpy(int beg, int end, char *dest, char *src)
{
  int		i;
  int		a;

  i = beg -1;
  a = 0;
  while (end > 0 && src[++i] != '\0')
    {
      dest[a] = src[i];
      --end;
      ++a;
    }
  return (dest);
}

int		strtolimit(char *text, int place, char limit)
{
  unsigned int	size;

  if (place > (int)strlen(text))
    return (0);
  size = place;
  while (text[size] != '\0' && text[size] != limit)
    ++size;
  return (size - place);
}

char		*my_epurstr(char *text)
{
  int		i;
  int		a;
  char		*ret;

  if ((ret = malloc((strlen(text) + 1) * sizeof(char))) == NULL)
    return ("fail");
  ret[strlen(text)] = 0;
  i = -1;
  a = -1;
  while (text[++i] != '\0')
    {
      if (text[i] == ' ')
	{
	  while (text[++i] == ' ');
	  ret[++a] = ' ';
	  ret[++a] = text[i];
	}
      else
	ret[++a] = text[i];
    }
  return (ret);
}

char		**explode(char *text, char limit)
{
  t_wordtab	a;

  text = my_epurstr(text);
  a.c = 0;
  a.nb = -1;
  a.i = -1;
  a.b = 2;
  while (text[++(a.i)] != '\0')
    if (text[a.i] == limit)
      ++a.b;
  if ((a.tab = malloc((a.b) * sizeof(char *))) == NULL)
    return (NULL);
  while (++a.nb != a.b)
    {
      a.tab[a.nb] = malloc((strtolimit(text, a.c, limit) + 1) * sizeof(char));
      if (a.tab[a.nb] == NULL)
	return (NULL);
      strnncpy(a.c, strtolimit(text, a.c, limit), a.tab[a.nb], text);
      a.tab[a.nb][strtolimit(text, a.c, limit)] = '\0';
      a.c += strtolimit(text, a.c, limit) + 1;
    }
  a.tab[a.nb - 1] = NULL;
  return (a.tab);
}
