/*
** vrb.c for serv in /home/la-val_c/rendu/PSU/myirc/serv
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Thu Apr 09 10:16:41 2015 Cyril La Valle
** Last update Sun Apr 12 21:24:44 2015 Cyril La Valle
*/

#include <stdio.h>
#include <stdlib.h>
#include "vrb.h"

/*
** malloc(2) a VRB (using PAGESIZE * 2 memory) and init it, ready for use
** returns a pointer to it's handler
*/
void		*vrb_creat(void)
{
  struct s_vrb	*vrb;
  long		size;

  if (-1 == (size = sysconf(_SC_PAGESIZE)))
    size = 4092L;
  if (NULL == (vrb = malloc((size_t) size * 2)))
    return (NULL);
  vrb->msize = (size_t) size - (size_t) sizeof(*vrb);
  vrb->lower_bound = ((char *) (vrb + 1));
  vrb->upper_bound = ((char *) vrb) + (size_t) size;
  vrb->begin = vrb->lower_bound;
  vrb->end = vrb->lower_bound;
  return (vrb);
}

ssize_t		vrb_spn(struct s_vrb *vrb, char *accept)
{
  size_t	cend;
  size_t	spn;

  cend = vrb->msize - (size_t) VRB_GET_REMAINING(vrb);
  spn = 0;
  for (spn = 0; spn < cend; ++spn)
    if (NULL != strchr(accept, vrb->begin[spn]))
      return (spn);
  return (-1);
}

size_t	vrb_get_space(struct s_vrb *vrb)
{
  return ((size_t) VRB_GET_REMAINING(vrb));
}

int	vrb_is_empty(struct s_vrb *vrb)
{
  return (VRB_IS_EMPTY(vrb));
}

void	vrb_destroy(struct s_vrb *vrb)
{
  free(vrb);
}
