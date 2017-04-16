/*
** get_val_from_node.c for get_val_from_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Apr 15 13:52:02 2017 Arthur Knoepflin
** Last update Sat Apr 15 14:22:10 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "my.h"

static int	get_len(char *obj)
{
  int		i;

  i = 0;
  while (obj[i] && obj[i] != '"')
    i += 1;
  return (i);
}

char	*get_val_from_node(char *obj, char *getter)
{
  int	i;
  int	j;
  char	*ret;

  i = my_strlen(getter) + 1;
  if ((ret = malloc(sizeof(char) * (get_len(obj + i) + 1))) == NULL)
    return (NULL);
  ret[get_len(obj + i)] = '\0';
  j = 0;
  while (j < get_len(obj + i))
    {
      ret[j] = obj[i + j];
      j += 1;
    }
  return (ret);
}
