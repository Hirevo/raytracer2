/*
** add_obj.c for add_obj in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 19 21:26:13 2017 Arthur Knoepflin
** Last update Tue May 23 22:48:00 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"

static void	assign(t_p_obj *new, t_p_obj add)
{
  new->next = NULL;
  new->type = add.type;
  new->pos = add.pos;
  new->rot = add.rot;
  new->p1 = add.p1;
  new->p2 = add.p2;
  new->rad = add.rad;
  new->file = add.file;
  new->obj_parse = add.obj_parse;
  new->aper = add.aper;
  new->col = add.col;
  new->buffer = add.buffer;
  new->height = add.height;
  new->reflect = add.reflect;
  new->refract = add.refract;
  new->refr_index = add.refr_index;
  new->spec_coef = add.spec_coef;
}

int		add_obj(t_p_obj **list, t_p_obj add)
{
  t_p_obj	*new;
  t_p_obj	*sauv;

  if ((new = malloc(sizeof(t_p_obj))) == NULL)
    return (1);
  sauv = *list;
  assign(new, add);
  if (*list)
    {
      while (sauv && sauv->next)
	sauv = sauv->next;
      sauv->next = new;
    }
  else
    *list = new;
  return (0);
}
