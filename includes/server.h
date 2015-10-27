/*
** server.h for MyIRC in /home/sin/rendu/PSU_tek2/PSU_2014_myirc/includes
**
** Made by SiN
** Login   <sin@epitech.net>
**
** Started on  Mon Apr  6 09:11:52 2015 SiN
** Last update Sun Apr 12 23:33:26 2015 Cyril La Valle
*/

#ifndef SERVER
#define SERVER

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <assert.h>
#include <err.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "array.h"
#include "queue.h"
#include "str.h"
#include "vartable.h"
#include "vrb.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

struct			s_cnx_handle
{
  void			*read_vrb;
  struct s_queue	*write_queue;
  int			sockfd;
};

struct		s_fdselect
{
  fd_set	read;
  fd_set	write;
};

struct	s_irc_client;
struct	s_irc_server;

typedef void (t_irc_cmd_func)(struct s_irc_client *,
			      struct s_irc_server *,
			      char const *,
			      char const **);

typedef t_vartable t_cnx_handle_vta;
typedef t_vartable t_irc_client_vta;

struct			s_irc_server
{
  int			topfd;
  int			sockfd;
  struct s_fdselect	*fd_req;
  struct s_fdselect	*fd_res;
  struct s_chan_list	*chan_list;
  t_cnx_handle_vta	*connexions;
  t_irc_client_vta	*clients;
};

struct			s_irc_chan
{
  char			name[255];
  char			*topic;
  struct s_cli_list	*clients;
};

struct			s_irc_client
{
  sa_family_t		family;
  in_port_t		port;
  in_addr_t		address;
  struct s_cnx_handle	*cnx;
  struct s_chan_list	*chan_list;
  char			nick[255];
  char			user[255];
  time_t	      	timestamp;
  char			pong;
  char			login;
  t_irc_cmd_func	*command;
};

struct			s_chan_list
{
  struct s_chan_list	*next;
  struct s_irc_chan	*data;
};

struct			s_cli_list
{
  struct s_cli_list	*next;
  struct s_irc_client	*data;
};

#define BRANCH_TABLE struct s_branch_table

struct	s_branch_table
{
  char	*name;
  void	*sptr;
};

int srv_init(struct s_irc_server **, int argc, char **argv);
int srv_lift(struct s_irc_server *);
int srv_shutdown(struct s_irc_server *);

void sockaddr_in_set(struct sockaddr_in *, sa_family_t, in_port_t, in_addr_t);

/*
** serv/branch.c
*/
void *branch(BRANCH_TABLE const *table, char const *symbol);

/*
** serv/c.c
*/
#define IRC_COMMAND_DECL(x) void x(PP1__, PP2__, PP3__, PP4__)
#define PP1__ struct s_irc_client *
#define PP2__ struct s_irc_server *
#define PP3__ char const *
#define PP4__ char const **
IRC_COMMAND_DECL(away_c);
IRC_COMMAND_DECL(join_c);
IRC_COMMAND_DECL(list_c);
IRC_COMMAND_DECL(motd_c);
IRC_COMMAND_DECL(user_c);
IRC_COMMAND_DECL(names_c);
IRC_COMMAND_DECL(nick_c);
IRC_COMMAND_DECL(part_c);
IRC_COMMAND_DECL(pass_c);
IRC_COMMAND_DECL(privmsg_c);
IRC_COMMAND_DECL(quit_c);
IRC_COMMAND_DECL(cli_command);
IRC_COMMAND_DECL(cli_command_login);
#undef PP1__
#undef PP2__
#undef PP3__
#undef PP4__
#undef IRC_COMMAND_DECL

/*
** serv/client_cnx.c
*/
void cli_cnx_read(struct s_irc_client *, struct s_irc_server *);
void cli_cnx_write(struct s_irc_client *, struct s_irc_server *);
void cli_interpret_command(struct s_irc_client *, struct s_irc_server *);
void cli_reply(struct s_irc_client *, struct s_irc_server *,
	       char const *fmt, ...);

/*
** serv/cnx.c
*/
struct s_cnx_handle *cnx_handle_creat(int sockfd);

/*
** serv/irc_client.c
*/
struct s_irc_client *irc_client_creat(void);

/*
** serv/lift.c
*/
void src_fdset_flip(struct s_irc_server *);
void srv_safe_ch_callback(struct s_irc_server *, size_t cb_off, int fd);
void srv_select(struct s_irc_server *);
void srv_deal(struct s_irc_server *);
int srv_lift(struct s_irc_server *);

/*
** serv/server_cnx.c
*/
void srv_cnx_read(struct s_irc_server *this, struct s_cnx_handle *cnx);

/*
** serv/vartable.c
*/
struct s_vartable *vta_creat(size_t step);
int vta_put(struct s_vartable *this, size_t index, void *entry);
void *vta_get(struct s_vartable *this, size_t index);
void vta_destroy(struct s_vartable *this);

struct s_irc_chan *chn_find_or_create(struct s_chan_list *,
				      char const *);
struct s_irc_chan *chn_find(struct s_chan_list *, char const *);
int chn_join(struct s_irc_chan *, struct s_irc_client *,
	     struct s_irc_server *);
struct s_irc_client *srv_find_client_by_nick(struct s_irc_server *,
					     char const *);
void cli_disconnect(struct s_irc_client *, struct s_irc_server *);
void chn_part(struct s_irc_chan *chan,
	      struct s_irc_client *cli,
	      struct s_irc_server *srv);

#endif /* SERVER */
