/*
** get_pos_from_node.c for get_pos_from_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 17:45:19 2017 Arthur Knoepflin
** Last update Fri Apr 21 14:51:10 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static char	*get_pos(char *str, int idx)
{
  sfVector2i	born;
  int		i;

  i = 0;
  born.x = 0;
  born.y = my_strlen(str);
  while (str[i] && idx >= 0)
    {
      if (idx == 0)
	{
	  while (str[i] && str[i] != ',' &&
		 ((str[i] < '0' || str[i] > '9') && str[i] != '-'))
	    i += 1;
	  born.x = i;
	  while (str[i] && str[i] != ',' &&
		 ((str[i] >= '0' && str[i] <= '9') || str[i] == '-'))
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

static sfVector2f	init_pos(void)
{
  sfVector2f		ret;

  ret.x = 0;
  ret.y = 0;
  return (ret);
}

sfVector2f	get_pos2_from_node(char *obj, char *name)
{
  sfVector2f	ret;
  char		*tmp;
  char		*pos;

  ret = init_pos();
  if ((pos = get_val_from_node(obj, name)) == NULL)
    return (ret);
  if ((tmp = get_pos(pos, 0)) == NULL)
    return (ret);
  ret.x = getnbr_parse(tmp);
  free(tmp);
  if ((tmp = get_pos(pos, 1)) == NULL)
    return (ret);
  ret.y = getnbr_parse(tmp);
  free(tmp);
  return (ret);
}
