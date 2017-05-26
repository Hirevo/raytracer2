/*
** raytrace.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Mar 27 00:22:54 2017 Nicolas Polomack
** Last update Fri May 26 05:11:37 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

sfVector3f	prepare(sfVector3f vec, t_obj *obj, int i)
{
  if (i)
    {
      vec.x -= obj->pos.x;
      vec.y -= obj->pos.y;
      vec.z -= obj->pos.z;
    }
  anti_rotation(&vec, &obj->r);
  return (vec);
}

sfVector3f	anti_prepare(sfVector3f vec, t_obj *obj, int i)
{
  rotation(&vec, &obj->r);
  if (i)
    {
      vec.x += obj->pos.x;
      vec.y += obj->pos.y;
      vec.z += obj->pos.z;
    }
  return (vec);
}

float	gather_dist(t_thread *t, int i)
{
  if (t->params->objs[i].type == -1)
    {
      if (t->params->objs[i].obj_parse != NULL)
	return (get_dist_obj(prepare(t->ray.orig, &(t->params->objs[i]), 1),
			     prepare(t->ray.dir, &(t->params->objs[i]), 0),
			     t->params->objs[i].obj_parse, &t->idx));
      else
	return (-1);
    }
  else
    return (t->params->intersect[t->params->id[(int)t->params->objs[i].type]]
	    (prepare(t->ray.orig, &(t->params->objs[i]), 1),
	     prepare(t->ray.dir, &(t->params->objs[i]), 0),
	     &(t->params->objs[i])));
}

void	prepare_raytrace(t_thread *t)
{
  t->depth = 0;
  t->from = NULL;
  t->refr = 1;
  t->primary = 1;
  t->ray.dir = calc_dir_vector(t->params->screen_size,
			       t->screen_pos.x,
			       t->screen_pos.y, t->params->config.fov);
  rotation(&t->ray.dir, &t->params->r);
}

sfColor		raytrace(t_thread *t)
{
  int		i;
  t_obj		*obj;
  float		dist;
  float		temp;

  i = -1;
  obj = NULL;
  dist = -1.0F;
  t->dir = t->ray.dir;
  while (++i < t->params->nb_objs)
    {
      temp = gather_dist(t, i);
      if (temp != -1.0F && (dist == -1.0F || temp < dist) &&
	&(t->params->objs[i]) != t->from)
	{
	  dist = temp;
	  obj = &(t->params->objs[i]);
	}
    }
  if (dist == -1)
    return (sfBlack);
  t->recur_start = t->ray.orig;
  return (apply_effects(t, obj, dist));
}
