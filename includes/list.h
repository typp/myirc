/*
** list.h for includes in /home/la-val_c/rendu/PSU/myirc/includes
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 19:55:04 2015 Cyril La Valle
** Last update Sun Apr 12 19:56:37 2015 Cyril La Valle
*/

#ifndef LIST_H
#define LIST_H

struct		s_list
{
  struct s_list	*next;
  void		*data;
};

struct s_list *list_alloc(void);
int           list_add(struct s_list *this, void *data);

#endif
