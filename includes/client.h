/*
** client.h for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/includes
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Mon Apr  6 09:11:52 2015 
** Last update Sun Apr 12 23:33:52 2015 Cyril La Valle
*/

#ifndef CLIENT
# define CLIENT

#include <limits.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>

typedef struct	s_server t_server;
typedef struct	s_channel t_channel;
typedef struct	s_user t_user;
typedef int	(*func)(char **, int, t_user *);

struct		s_server
{
  char		*srvname;
  t_channel	*chans;
};

struct		s_channel
{
  char		*name;
  t_channel	*next;
};

struct		s_user
{
  int		isco;
  t_server	*srvs;
  char		*nick;
  char		*oldnick;
  char		*real;
  char		*host;
  char		*current;
};

typedef struct	s_command
{
  char		*command;
  func		act;
}		t_command;

/* sorry */

typedef struct	s_wordtab
{
  int		i;
  int		b;
  char		**tab;
  int		c;
  int		nb;
}		t_wordtab;

/*
** command.c
*/
int		nick(char **tab, int socket, t_user *user);
int		list(char **tab, int socket, t_user *user);
int		join(char **tab, int socket, t_user *user);
int		part(char **tab, int socket, t_user *user);
int		users(char **tab, int socket, t_user *user);
int		private(char **tab, int socket, t_user *user);

/*
** explode.c
*/
char		*strnncpy(int beg, int end, char *dest, char *src);
int		strtolimit(char *text, int place, char limit);
char		*my_epurstr(char *text);
char		**explode(char *text, char limit);

/*
** handshake.c
*/
int		do_handshake(t_user *user, int sock);
int		nick_hdsh(t_user *user, int sock);
int		user_hdsh(t_user *user, int socket);

/*
** main.c
*/
void		doit(char *buffer, t_user *usr, int sock, int ret);
char		**new_client(t_user *user);
int		chat(t_user *user, int sock, const struct sockaddr_in *sin,
		     char *srvname);
int		connection(char *get, t_user *user);

/*
** misc.c
*/
char		*pmt_line(char *pmt);
int		add_it(t_user *user, char *srvnam);
void		welcome(void);
void		proper_exit(char **command);
void		send_proper(int sock, t_user *user);
void		format_recp(int sock, t_user *user);
void		listing(char *str);
int		isnumeric(char *str);

/*
** my_implode.c
*/
char		*implode(char **w_tab, char sep);

/*
** utils.c
*/
void		setwell(char *buffer, int ret, int sock);
int		lentab(char **tab);

#endif /* CLIENT */
