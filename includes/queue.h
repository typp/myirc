/*
** queue.h for includes in /home/la-val_c/rendu/PSU/myirc/includes
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 13:38:15 2015 Cyril La Valle
** Last update Sun Apr 12 14:11:52 2015 Cyril La Valle
*/

#ifndef QUEUE_H
#define QUEUE_H

struct			s_queue_node
{
  struct s_queue_node	*next;
  char			*data;
};

struct			s_queue
{
  struct s_queue_node	*nodes;
};

struct s_queue      *queue_creat(void);
struct s_queue_node *queue_node_alloc(void);
struct s_queue_node *queue_node_get_last(struct s_queue_node *nptr);
int                 queue_push(struct s_queue *this, char const *data);
char                *queue_front(struct s_queue *this);
void                queue_pop(struct s_queue *this);
int                 queue_is_empty(struct s_queue *this);
void                queue_destroy(struct s_queue *this);

#endif
