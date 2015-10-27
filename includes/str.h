/*
** str.h for includes in /home/la-val_c/rendu/PSU/myirc/includes
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:53:40 2015 Cyril La Valle
** Last update Sun Apr 12 19:58:41 2015 Cyril La Valle
*/

#ifndef STR_H
#define STR_H

typedef struct s_wordtab t_wordtab;
struct		s_wordtab
{
  int		i;
  int		b;
  char		**tab;
  int		c;
  int		nb;
};

int     strcut(char **dest, char *src, int);
int     strscut(char **dest, char *src, char *);
char    **strsplit(char *, int);
char    *strupper(char *);
ssize_t stralcat(char **buffer, char const *s1, char const *s2);
char    **explode(char *text, char limit);

#endif
