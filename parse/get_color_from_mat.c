/*
** get_color_from_mat.c for get_col_from_mat in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 20:43:08 2017 Arthur Knoepflin
** Last update Sun May 28 18:28:36 2017 Arthur Knoepflin
*/

#include "raytracer.h"
#include "my.h"

static t_material	*search_mat(char *name, t_material *l_mat)
{
  t_material		*cpy;

  cpy = l_mat;
  while (cpy)
    {
      if (!my_strcmp(cpy->name, name) && cpy->type == 1)
	return (cpy);
      cpy = cpy->next;
    }
  return (NULL);
}

static sfColor	init_color(void)
{
  sfColor	ret;

  ret.r = 255;
  ret.g = 255;
  ret.b = 255;
  ret.a = 255;
  return (ret);
}

sfColor		get_col_from_mat(char *obj,
				 char *name,
				 t_material *l_mat)
{
  sfColor	ret;
  t_material	*mat;
  char		*name_mat;

  ret = init_color();
  if ((name_mat = get_val_from_node(obj, name)) == NULL)
    return (ret);
  if ((mat = search_mat(name_mat, l_mat)) == NULL)
    return (ret);
  return (mat->color);
}
