/*
** array.h for includes in /home/la-val_c/rendu/PSU/myirc/includes
**
** Made by Cyril La Valle
** Login   <la-val_c@epitech.eu>
**
** Started on  Sun Apr 12 18:57:30 2015 Cyril La Valle
** Last update Sun Apr 12 18:59:29 2015 Cyril La Valle
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

char   **make_str_array(char *, ...) __attribute__ ((sentinel));
int    append_to_str_array(char ***arrptr, char *str);
void   parray(char **array);
size_t arrlen(char const **);

#endif
