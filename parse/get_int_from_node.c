/*
** get_int_from_node.c for get_int_from_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 19 23:00:34 2017 Arthur Knoepflin
** Last update Thu Apr 20 15:34:25 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static char	*extract(char *str)
{
  int		i;

  i = 0;
  while (str[i] && (str[i] == '-' || str[i] == '+' ||
		    (str[i] >= '0' && str[i] <= '9')))
    i += 1;
  return (my_strndup(str, i));
}

float	get_int_from_node(char *obj, char *getter)
{
  float	ret;
  char	*tmp;

  if ((tmp = extract(obj + my_strlen(getter))) == NULL)
    return (0);
  ret = getnbr_parse(tmp);
  free(tmp);
  return (ret);
}

float	get_pint_from_node(char *obj, char *getter)
{
  float	ret;

  ret = get_int_from_node(obj, getter);
  if (ret < 0)
    return (0);
  return (ret);
}
