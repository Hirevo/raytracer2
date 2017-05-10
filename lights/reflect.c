/*
** reflect.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Mar 28 20:37:50 2017 Nicolas Polomack
** Last update Wed May 10 14:14:15 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"

sfColor		apply_effects(t_thread *t, t_obj *obj, float dist)
{
  sfColor	col;
  sfVector3f	imp;

  prepare_light_calc(t, obj, dist);
  imp = prepare(t->impact, obj, 1);
  col = t->params->apply_tex[t->params->id[(int)obj->type]](imp, obj);
  col = calc_lights(t, obj, col);
  col = light_effects(t, obj, col);
  return (col);
}

void	prepare_light_ray(t_thread *t, int i)
{
  t->ray.dir.x = t->params->lights[i].pos.x - t->impact.x;
  t->ray.dir.y = t->params->lights[i].pos.y - t->impact.y;
  t->ray.dir.z = t->params->lights[i].pos.z - t->impact.z;
}

float		prepare_reflect(t_thread *t)
{
  float		norme;

  t->ray.orig = t->impact;
  t->normal = normalize(t->normal);
  t->ray.dir = normalize(t->ray.dir);
  norme = -dot(t->normal, t->ray.dir);
  t->ray.dir.x = t->ray.dir.x + (2.0F * t->normal.x * norme);
  t->ray.dir.y = t->ray.dir.y + (2.0F * t->normal.y * norme);
  t->ray.dir.z = t->ray.dir.z + (2.0F * t->normal.z * norme);
  return (norme);
}

sfColor		apply_effect(sfColor col, sfColor reflect, float ratio)
{
  col.r = ((float)reflect.r) * ratio +
    ((float)col.r) * (1.0F - ratio);
  col.g = ((float)reflect.g) * ratio +
    ((float)col.g) * (1.0F - ratio);
  col.b = ((float)reflect.b) * ratio +
    ((float)col.b) * (1.0F - ratio);
  col.a = 255;
  return (col);
}

sfColor		light_effects(t_thread *t, t_obj *obj, sfColor col)
{
  sfColor	r[2];
  float		c1;
  t_thread	save;

  if (t->depth++ < t->params->config.reflect_depth)
    {
      t->primary = 0;
      t->from = obj;
      t->ray.dir = t->dir;
      save = *t;
      c1 = prepare_reflect(t);
      if (obj->reflect > 0)
	r[0] = apply_effect(col, raytrace(t), obj->reflect);
      *t = save;
      prepare_refract(t, c1, obj->refr_index);
      t->refr = obj->refr_index;
      if (obj->refract > 0)
	r[1] = apply_effect(col, raytrace(t), obj->refract);
      if (obj->refract > 0)
	if (!(obj->reflect > 0))
	  return (r[1]);
	else
	  return (average_colors(r, 2));
      else if (obj->reflect > 0)
	return (r[0]);
      return (col);
    }
  return (col);
}
