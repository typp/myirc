/*
** vrb_into.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 21:23:15 2015 Cyril La Valle
** Last update Sun Apr 12 23:29:25 2015 Cyril La Valle
*/

#include <stdio.h>
#include <stdlib.h>
#include "vrb.h"

/*
** internal function, called in case the buffer goes ahead from upper_bound
*/
static void	vrb_backroll(struct s_vrb *vrb)
{
  size_t	size;

  size = VRB_GET_REMAINING(vrb);
  memcpy(vrb->lower_bound, vrb->begin, size);
  vrb->begin = vrb->lower_bound;
  vrb->end = vrb->lower_bound + size;
}

/*
** write(2) *size* bytes over the specified fd from the VRB, *size* may be
** reduced if there is not enough bytes stored in the VRB
** return as write(2) call returns
*/
ssize_t		vrb_write(int fd, struct s_vrb *vrb, size_t size)
{
  size_t	least_size;
  size_t	rem_size;
  ssize_t	rt;

  errno = 0;
  rem_size = (size_t) VRB_GET_REMAINING(vrb);
  if (rem_size == vrb->msize)
    return (0);
  least_size = MIN(rem_size, size);
  rt = write(fd, vrb->begin, least_size);
  if (0 < rt)
    {
      vrb->begin += rt;
      if (vrb->begin >= vrb->upper_bound)
	vrb_backroll(vrb);
    }
  return (rt);
}

/*
** send(2)
*/
ssize_t		vrb_socket_send(int fd, struct s_vrb *vrb, int flags)
{
  size_t	size;
  ssize_t	rt;

  errno = 0;
  size = (size_t) VRB_GET_REMAINING(vrb);
  if (size == vrb->msize)
    return (0);
  rt = send(fd, vrb->begin, size, flags);
  if (0 < rt)
    {
      vrb->begin += rt;
      if (vrb->begin >= vrb->upper_bound)
	vrb_backroll(vrb);
    }
  return (rt);
}

/*
** take out maximum *size* bytes from the VRB, putting into *dest* with
** memcpy(2) *dest* may hold necessecary space as specified in *size*
** return the amount of bytes moved into *dest*
*/
size_t		vrb_quarry(char *dest, struct s_vrb *vrb, size_t size)
{
  size_t	least_size;
  size_t	rem_size;

  errno = 0;
  if (size == 0)
    return (0);
  rem_size = (size_t) VRB_GET_REMAINING(vrb);
  if (rem_size == vrb->msize)
    return (0);
  least_size = MIN(rem_size, size);
  memcpy(dest, vrb->begin, least_size);
  vrb->begin += least_size;
  if (vrb->begin >= vrb->upper_bound)
    vrb_backroll(vrb);
  return (least_size);
}
