/*
** utils.c for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Sun Apr 12 02:20:22 2015 
** Last update Sun Apr 12 22:29:04 2015 
*/

#include "client.h"

void		setwell(char *buffer, int ret, int sock)
{
  int		place;

  place = 0;
  buffer[ret] = 0x0D;
  buffer[ret + 1] = 0x0A;
  while (place != ret + 2)
    place += write(sock, buffer + place, (ret + 2 - place));
}

int			lentab(char **tab)
{
  int			i;

  for (i = 0; tab[i]; ++i);
  return (i);
}

void		listing(char *str)
{
  char		**tab;

  tab = explode(str, ' ');
  printf("%s\n", tab[1]);
}

int		isnumeric(char *str)
{
  if (str[0] >= 48 && str[0] <= 57
      && str[1] >= 48 && str[1] <= 57
      && str[2] >= 48 && str[2] <= 57)
    return (1);
  return (0);
}
