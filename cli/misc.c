/*
** misc.c for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Sun Apr 12 02:21:11 2015
** Last update Sun Apr 12 23:33:23 2015 
*/

#include "client.h"

void		format_recp(int sock, __attribute__((unused))t_user *user)
{
  int		n;
  char		*buffer;
  char		**tab;
  int		place;

  if ((buffer = malloc(4096 * sizeof(char))) == NULL)
    return ;
  n = read(sock, buffer, 4095);
  if (n <= 0)
    exit(1);
  buffer[n - 1] = 0;
  buffer[n - 2] = 0;
  buffer[n] = 0;
  tab = explode(buffer, '\n');
  for (place = 0; tab[place] != NULL; ++place)
    {
      printf("%s\n", tab[place]);
      if (strncmp("421", tab[place], 3) &&
	  strncmp("321", tab[place], 3) &&
	  strncmp("323", tab[place], 3))
	if (!strncmp("322", tab[place], 3))
	  listing(tab[place]);
    }
}

void		send_proper(int sock, t_user *user)
{
  int		n;
  char		*buffer;
  int		i;

  if ((buffer = malloc(4096 * sizeof(char))) == NULL)
    return ;
  n = read(0, buffer, 4095);
  buffer[n - 1] = 0;
  for (i = 0; buffer[i]; ++i)
    if (buffer[i] == '\n')
      buffer[i] = ' ';
  if (n > 0)
    doit(buffer, user, sock, n);
  else if (n < 0)
    puts("an error occured exiting now");
}

char		*pmt_line(char *pmt)
{
  char		*buffer;
  int		ret;

  if ((buffer = calloc(1, 1024 * sizeof(char))) == NULL)
    return (NULL);
  write(1, "client <", 8);
  write(1, pmt, strlen(pmt));
  write(1, "> ", 2);
  if ((ret = read(0, buffer, 1023)) <= 0)
    {
      free(buffer);
      return (NULL);
    }
  buffer[ret - 1] = 0;
  return (buffer);
}

int		add_it(t_user *user, char *srvnam)
{
  if ((user->srvs = malloc(sizeof(t_server))) == NULL)
    return (-1);
  if ((user->srvs->srvname = strdup(srvnam)) == NULL)
    return (-1);
  user->srvs->chans = NULL;
  return (0);
}

void		welcome(void)
{
  printf("\033[94mWelcome to the irc client\n");
  printf("\033[92mhere is a small list of all the command\n");
  printf("\033[91m/server\033[0m to connect to a server default port ");
  printf("6667 otherwise :[port]\n");
  printf("\033[91m/part\033[0m to leave a server\n");
  printf("\033[91m/join\033[0m to join a channel\n");
  printf("\033[91m/nick\033[0m to change your nick\n");
  printf("\033[91m/user\033[0m to get the list of user\n");
  printf("\033[91m/list\033[0m to get the list of channel possible");
  printf("to put a string");
  printf("to get all the channel with this string in his name\n");
  printf("\033[91m/send_file\033[0m to connect to send a file #yolo\n");
  printf("\033[91m/accept_file\033[0m to accept a file #yolo2\n");
  printf("\n\n\033[94menjoy\033[0m\n\n\n");
}
