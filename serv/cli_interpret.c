/*
** cli_interpret.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:37:33 2015 Cyril La Valle
** Last update Sun Apr 12 23:30:25 2015 Cyril La Valle
*/

#include "server.h"

int	cli_parse_command_single_arg(char ***args, char *raw_arg)
{
  if (NULL == (*args = make_str_array(raw_arg + 1, NULL)))
    {
      warn("Cannot interpret client command");
      free(raw_arg);
      return (-1);
    }
  return (0);
}

int	cli_parse_command_multi_arg(char ***args, char *raw_arg)
{
  char	*last_arg;

  strscut(&last_arg, raw_arg, " :");
  *args = explode(raw_arg, ' ');
  if (NULL != last_arg)
    if (-1 == append_to_str_array(args, last_arg))
      {
	warn("Cannot interpret client command");
	free(raw_arg);
	free(last_arg);
	return (-1);
      }
  return (0);
}

int	cli_parse_command(char *input, char ***args)
{
  char	*raw_arg;

  if (-1 != strcut(&raw_arg, input, ' '))
    {
      if (raw_arg[0] == ':')
	{
	  if (0 > cli_parse_command_single_arg(args, raw_arg))
	    return (-1);
	}
      else
	{
	  if (0 > cli_parse_command_multi_arg(args, raw_arg))
	    return (-1);
	}
    }
  else if (NULL == (*args = calloc(1, sizeof(**args))))
    return (-1);
  return (0);
}

void		cli_interpret_command(struct s_irc_client *this,
				      struct s_irc_server *server)
{
  char		*input;
  char		**args;
  ssize_t	span;
  ssize_t	bytes;

  span = vrb_spn(this->cnx->read_vrb, "\n");
  while (0 <= span)
    {
      ++span;
      input = malloc(span);
      if (0 > (bytes = vrb_quarry(input, this->cnx->read_vrb, span)))
	return ;
      input[bytes - 1] = '\0';
      if (input[bytes - 2] == '\r')
	--bytes;
      if (bytes > 0)
	{
	  input[--bytes] = '\0';
	  printf("[%s] %s\n", inet_ntoa(*((struct in_addr *) &this->address)), input);
	  if (0 == cli_parse_command(input, &args))
	    this->command(this, server, strupper(input), (const char **) args);
	}
      free(input);
      span = vrb_spn(this->cnx->read_vrb, "\n");
    }
}
