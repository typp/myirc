/*
** cli_hooks.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:39:21 2015 Cyril La Valle
** Last update Sun Apr 12 23:16:18 2015 Cyril La Valle
*/

#include "server.h"

static struct s_branch_table const	irc_command_table[] =
{
    {"AWAY", &away_c},
    {"JOIN", &join_c},
    {"LIST", &list_c},
    {"MOTD", &motd_c},
    {"NAMES", &names_c},
    {"NICK", &nick_c},
    {"PART", &part_c},
    {"PRIVMSG", &privmsg_c},
    {"QUIT", &quit_c},
    {NULL, NULL}
};

void	cli_command(struct s_irc_client *this,
		    struct s_irc_server *srv,
		    char const *name, char const **args)
{
  void	(*command)(struct s_irc_client *this,
		    struct s_irc_server *srv,
		    char const *name, char const **args);

  if (strlen(name))
    {
      if (NULL != (command = branch(irc_command_table, name)))
	{
	  command(this, srv, name, args);
	}
      else
	{
	  cli_reply(this, srv, "421: %s %s :Unknown command", this->nick, name);
	}
    }
}

void	cli_command_login(struct s_irc_client *this,
			  struct s_irc_server *srv,
			  char const *cmd,
			  char const **args)
{
  if (strlen(cmd))
    {
      if (strcmp(cmd, "NICK") == 0)
	nick_c(this, srv, cmd, args);
      else if (strcmp(cmd, "USER") == 0)
	user_c(this, srv, cmd, args);
      else if (strcmp(cmd, "PASS") == 0)
	pass_c(this, srv, cmd, args);
      else
	{
	  cli_reply(this, srv, "421: * %s :Unknown command", cmd);
	  return ;
	}
      if (strlen(this->nick) && strlen(this->user))
	{
	  this->login = TRUE;
	  this->command = &cli_command;
	  cli_reply(this, srv, "001 %s :Hi", this->nick);
	}
    }
}
