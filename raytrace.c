/*
** raytrace.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Mar 27 00:22:54 2017 Nicolas Polomack
** Last update Mon Mar 27 03:18:23 2017 Nicolas Polomack
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

float	gather_dist(t_params *params, int i)
{
  return (params->intersect[(int)params->objs[i].type]
	  (prepare(params->ray.orig, &(params->objs[i]), 1),
	   prepare(params->ray.dir, &(params->objs[i]), 0),
	   &(params->objs[i])));
}

void	prepare_light_calc(t_params *params, t_obj *obj, float dist)
{
  params->impact.x = params->ray.orig.x + params->ray.dir.x * dist;
  params->impact.y = params->ray.orig.y + params->ray.dir.y * dist;
  params->impact.z = params->ray.orig.z + params->ray.dir.z * dist;
  params->ray.orig = params->impact;
  params->ray.dir.x = params->lights[0].pos.x - params->impact.x;
  params->ray.dir.y = params->lights[0].pos.y - params->impact.y;
  params->ray.dir.z = params->lights[0].pos.z - params->impact.z;
  params->normal = prepare(params->impact, obj, 1);
  params->get_normal[(int)obj->type](params, obj);
  params->normal = anti_prepare(params->normal, obj, 0);
}

sfColor		raytrace(t_params *params)
{
  int		i;
  t_obj		*obj;
  float		dist;
  float		temp;

  i = -1;
  obj = NULL;
  dist = -1;
  while (++i < params->nb_objs)
    {
      temp = gather_dist(params, i);
      if (temp >= 0 && (dist == -1 || temp < dist))
	{
	  dist = temp;
	  obj = &(params->objs[i]);
	}
    }
  if (dist == -1)
    return (sfBlack);
  prepare_light_calc(params, obj, dist);
  if (is_obstructed(params, obj))
    return (sfBlack);
  return (eval_luminosity(params, obj->col));
}
