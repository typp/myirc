/*
** vrb.h for includes in /home/la-val_c/rendu/PSU/myirc/includes
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sat Apr 11 19:27:31 2015 Cyril La Valle
** Last update Sun Apr 12 12:01:19 2015 Cyril La Valle
*/

#ifndef VRB_H
#define VRB_H

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct		s_vrb
{
  size_t	msize;
  char		*lower_bound;
  char		*upper_bound;
  char		*begin;
  char		*end;
};

#define VRB_GET_DIST(p) (((uintptr_t) (p)->end) - ((uintptr_t) (p)->begin))
#define VRB_GET_REMAINING(p) (((uintptr_t) (p)->msize) - VRB_GET_DIST(p))
#define VRB_IS_EMPTY(p) ((p)->begin == (p)->end)

#define MIN(a, b) ((a) > (b) ? (b) : (a))

/*
** serv/vrb.c
*/
void    *vrb_creat(void);
ssize_t vrb_read(int fd, struct s_vrb *vrb, size_t size);
ssize_t vrb_write(int fd, struct s_vrb *vrb, size_t size);
ssize_t vrb_socket_recv(int fd, struct s_vrb *vrb, int flags);
ssize_t vrb_socket_send(int fd, struct s_vrb *vrb, int flags);
size_t  vrb_quarry(char *dest, struct s_vrb *vrb, size_t size);
size_t  vrb_put(struct s_vrb *vrb, char const *src, size_t size);
ssize_t vrb_spn(struct s_vrb *vrb, char *accept);
size_t  vrb_get_space(struct s_vrb *vrb);
int     vrb_is_empty(struct s_vrb *vrb);
void    vrb_destroy(struct s_vrb *vrb);

#endif
