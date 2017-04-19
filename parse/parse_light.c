/*
** parse_light.c for parse_light in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 16:58:57 2017 Arthur Knoepflin
** Last update Tue Apr 18 21:22:55 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static t_l_light	get_light(char *obj, int *i, t_material *l_mat)
{
  t_l_light		ret;

  while (obj[*i] && my_strncmp(obj + *i, "/>", 2))
    {
      if (!my_strncmp(obj + *i, POS_N, my_strlen(POS_N)))
	ret.pos = get_pos_from_node(obj + *i, POS_N);
      if (!my_strncmp(obj + *i, COLOR_N, my_strlen(COLOR_N)))
	ret.col = get_col_from_mat(obj + *i, COLOR_N, l_mat);
      *i += 1;
    }
  return (ret);
}

static sfColor	get_ambient(char *obj, int *i, t_material *l_mat)
{
  sfColor	ret;

  while (obj[*i] && my_strncmp(obj + *i, "/>", 2))
    {
      if (!my_strncmp(obj + *i, COLOR_N, my_strlen(COLOR_N)))
	ret = get_col_from_mat(obj + *i, COLOR_N, l_mat);
      *i += 1;
    }
  return (ret);
}

static void	parse_light_point(char *obj,
				  t_material *mat,
				  t_l_light **light,
				  sfColor *ambient)
{
  int		i;
  t_l_light	tmp;

  i = 0;
  while (obj[i])
    {
      if (!my_strncmp(obj + i, POINT, my_strlen(POINT)))
	{
	  tmp = get_light(obj, &i, mat);
	  add_light(light, tmp);
	}
      if (!my_strncmp(obj + i, AMBIENT, my_strlen(AMBIENT)))
	*ambient = get_ambient(obj, &i, mat);
      i += 1;
    }
}

t_p_light	*parse_light(char **file, t_material *material)
{
  char		*obj;
  t_p_light	*ret;

  if ((obj = get_head_node(file, LIGHT)) == NULL)
    return (NULL);
  if ((ret = malloc(sizeof(t_p_light))) == NULL)
    return (NULL);
  ret->light = NULL;
  parse_light_point(obj, material, &ret->light, &ret->ambient);
  return (ret);
}
