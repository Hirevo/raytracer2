/*
** assign_light.c for assign_light in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 21 13:30:38 2017 Arthur Knoepflin
** Last update Thu May 25 14:07:14 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static int	nb_obj(t_p_obj *list)
{
  int		ret;

  ret = 0;
  while (list)
    {
      ret += 1;
      list = list->next;
    }
  return (ret);
}

static void	assign_obj(t_obj *obj, t_p_obj *list)
{
  obj->type = list->type;
  obj->pos = list->pos;
  obj->r = list->rot;
  obj->p1 = list->p1;
  obj->p2 = list->p2;
  obj->rad = list->rad;
  obj->aper = list->aper;
  obj->col = list->col;
  obj->obj_parse = list->obj_parse;
  obj->file = list->file;
  obj->buffer = list->buffer;
  obj->height = list->height;
  obj->reflect = list->reflect;
  obj->refract = list->refract;
  obj->refr_index = list->refr_index;
  obj->spec_coef = list->spec_coef;
}

int	convert_obj(t_params *par, t_p_obj *list)
{
  int	i;

  par->nb_objs = nb_obj(list);
  if ((par->objs = malloc(sizeof(t_obj) * (nb_obj(list)))) == NULL)
    return (1);
  i = 0;
  while (list)
    {
      assign_obj(&(par->objs[i]), list);
      i += 1;
      list = list->next;
    }
  my_mset(par->objs, 0, sizeof(t_obj));
  return (0);
}
