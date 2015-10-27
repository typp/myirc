/*
** vrb_read.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 21:21:10 2015 Cyril La Valle
** Last update Sun Apr 12 21:30:23 2015 Cyril La Valle
*/

#include <stdio.h>
#include <stdlib.h>
#include "vrb.h"

/*
** recv(2) bytes on the fd into the VRB
** return same value as recv(2) call, except return 0 if the VRB is full
*/
ssize_t		vrb_socket_recv(int fd, struct s_vrb *vrb, int flags)
{
  size_t	size;
  ssize_t	rt;

  errno = 0;
  size = (size_t) VRB_GET_REMAINING(vrb);
  if (size == 0)
    return (-1);
  rt = recv(fd, vrb->end, size, flags);
  if (rt > 0)
    vrb->end += rt;
  return (rt);
}

/*
** read(2) *size* bytes on the fd into the VRB
** return same value as read(2) call, except if there is not enough free space
** in the VRB, size is reduced to it
*/
ssize_t		vrb_read(int fd, struct s_vrb *vrb, size_t size)
{
  size_t	least_size;
  size_t	rem_size;
  ssize_t	rt;

  errno = 0;
  rem_size = (size_t) VRB_GET_REMAINING(vrb);
  if (rem_size == 0)
    return (-1);
  least_size = MIN(rem_size, size);
  rt = read(fd, vrb->end, least_size);
  if (rt > 0)
    vrb->end += rt;
  return (rt);
}

/*
** put maximum *size* bytes from src into the VRB with memcpy(2)
** return amount of bytes copied into the VRB
*/
size_t		vrb_put(struct s_vrb *vrb, char const *src, size_t size)
{
  size_t	least_size;
  size_t	rem_size;

  errno = 0;
  rem_size = (size_t) VRB_GET_REMAINING(vrb);
  if (rem_size == 0)
    return (-1);
  least_size = MIN(rem_size, size);
  memcpy(vrb->end, src, least_size);
  vrb->end += least_size;
  return (least_size);
}
