/*
** main.c for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/cli
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Mon Mar 23 12:26:19 2015
** Last update Sun Apr 12 23:35:40 2015 
*/

#include "client.h"

void			sends(char *buffer, t_user *user, int sock)
{
  char			**tab;
  char			*data;

  if ((tab = malloc(4 * sizeof(char *))) == NULL)
     return ;
  tab[0] = strdup("PRIVMSG");
  tab[1] = strdup(user->current);
  tab[2] = strdup(buffer);
  tab[3] = NULL;
  data = implode(tab, ' ');
  setwell(data, strlen(data), sock);
}

void			doit(char *buffer, t_user *usr, int sock,
			     __attribute__((unused)) int ret)
{
  int			i;
  char			**tab;
  t_command		action[] = {
    {"/nick", nick},
    {"/join", join},
    {"/list", list},
    {"/users", users}
  };

  tab = explode(buffer, ' ');
  if (tab == NULL)
    return ;
  tab[lentab(tab) - 1][strlen(tab[lentab(tab) - 1])] = 0;
  for (i = 0; i < 4; ++i) {
    if (!strcmp(tab[0], action[i].command))
      return ((void)action[i].act(tab, sock, usr));
  }
  sends(buffer, usr, sock);
}

int			chat(t_user *user, int sock,
                             const struct sockaddr_in *sin, char *srvname)
{
  fd_set		reads;
  char			buff[4001];

  if (connect(sock, (struct sockaddr *)sin, sizeof(*sin)) == -1
      || add_it(user, srvname) == -1)
    return (-1);
  do_handshake(user, sock);
  read(sock, buff, 4000);
  while (1) {
    write(1, user->nick, strlen(user->nick));
    write(1, " ~> ", 4);
    FD_ZERO(&reads);
    FD_SET(0, &reads);
    FD_SET(sock, &reads);
    if (select(sock + 1, &reads, NULL, NULL, NULL) == -1)
      exit(1);
    if (FD_ISSET(sock, &reads))
      format_recp(sock, user);
    if (FD_ISSET(0, &reads))
      send_proper(sock, user);
  }
  return (0);
}

int                     connection(char *get, t_user *user)
{
  char			**tab;
  struct hostent	*he;
  struct sockaddr_in	sin;
  char			**connecter;
  int			sock;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  tab = explode(get, ' ');
  if (lentab(tab) != 2)
    return (-1);
  sin.sin_family = AF_INET;
  connecter = explode(tab[1], ':');
  if (lentab(connecter) == 1)
    sin.sin_port = htons(6667);
  else if (lentab(connecter) == 2 && atoi(connecter[1]) > 0
           && atoi(connecter[1]) <= USHRT_MAX)
    sin.sin_port = htons(atoi(connecter[1]));
  else
    return (-1);
  if ((he = gethostbyname(connecter[0])) == NULL)
    sin.sin_addr.s_addr = inet_addr(connecter[0]);
  else
    memcpy(&sin.sin_addr, he->h_addr_list[0], he->h_length);
  return (chat(user, sock, &sin, connecter[0]));
}

int             main(void)
{
  t_user	user;
  char		*get;

  welcome();
  user.isco = 0;
  user.srvs = NULL;
  user.oldnick = NULL;
  while (user.isco == 0)
    {
      if (!(get = pmt_line("\033[91mnot connected\033[0m")))
        user.isco = 1;
      else if (strncmp(get, "/server", 7))
        {
          puts("\033[93myou are not connected to a server !!!\033[0m\n");
          free(get);
        }
      else
        if (connection(get, &user) < 0)
          {
            puts("\033[91msomething bad append\033[0m");
            free(get);
            user.isco = 1;
          }
    }
  return (0);
}

