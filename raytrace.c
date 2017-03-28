/*
** raytrace.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Mar 27 00:22:54 2017 Nicolas Polomack
** Last update Wed Mar 29 01:48:44 2017 Nicolas Polomack
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
  anti_rotation(&vec, obj);
  return (vec);
}

sfVector3f	anti_prepare(sfVector3f vec, t_obj *obj, int i)
{
  rotation(&vec, obj);
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
  return (t->params->intersect[(int)t->params->objs[i].type]
	  (prepare(t->ray.orig, &(t->params->objs[i]), 1),
	   prepare(t->ray.dir, &(t->params->objs[i]), 0),
	   &(t->params->objs[i])));
}

void	prepare_light_calc(t_thread *t, t_obj *obj, float dist)
{
  t->impact.x = t->ray.orig.x + t->ray.dir.x * dist;
  t->impact.y = t->ray.orig.y + t->ray.dir.y * dist;
  t->impact.z = t->ray.orig.z + t->ray.dir.z * dist;
  t->ray.orig = t->impact;
  t->normal = prepare(t->impact, obj, 1);
  t->params->get_normal[(int)obj->type](t, obj);
  t->normal = anti_prepare(t->normal, obj, 0);
}

sfColor		raytrace(t_thread *t)
{
  int		i;
  t_obj		*obj;
  float		dist;
  float		temp;

  i = -1;
  obj = NULL;
  dist = -1;
  t->dir = t->ray.dir;
  while (++i < t->params->nb_objs)
    {
      temp = gather_dist(t, i);
      if (temp >= 0 && (dist == -1 || temp < dist) &&
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
