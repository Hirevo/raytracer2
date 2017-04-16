/*
** get_color_from_node.c for get_color_from_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Apr 15 14:25:50 2017 Arthur Knoepflin
** Last update Sat Apr 15 14:49:10 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static char	*get_nbr(char *str, int idx)
{
  sfVector2i	born;
  int		i;

  i = 0;
  while (str[i] && idx >= 0)
    {
      if (idx == 0)
	{
	  while (str[i] && str[i] != ',' && (str[i] < '0' || str[i] > '9'))
	    i += 1;
	  born.x = i;
	  while (str[i] && str[i] != ',' && (str[i] >= '0' && str[i] <= '9'))
	    i += 1;
	  born.y = i;
	}
      if (str[i] == ',')
	idx -= 1;
      if (str[i])
	i += 1;
    }
  return (my_strndup(str + born.x, born.y - born.x));
}

static sfColor	init_color(void)
{
  sfColor	ret;

  ret.r = -1;
  ret.g = -1;
  ret.b = -1;
  ret.a = -1;
  return (ret);
}

sfColor		get_color_from_node(char *obj, char *name)
{
  sfColor	ret;
  char		*tmp;
  char		*color;

  ret = init_color();
  if ((color = get_val_from_node(obj, name)) == NULL)
    return (ret);
  if ((tmp = get_nbr(color, 0)) == NULL)
    return (ret);
  ret.a = 255;
  ret.r = my_getnbr(tmp);
  free(tmp);
  if ((tmp = get_nbr(color, 1)) == NULL)
    return (ret);
  ret.g = my_getnbr(tmp);
  free(tmp);
  if ((tmp = get_nbr(color, 2)) == NULL)
    return (ret);
  ret.b = my_getnbr(tmp);
  free(tmp);
  free(color);
  return (ret);
}
