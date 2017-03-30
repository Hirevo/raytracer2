/*
** reflect.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Mar 28 20:37:50 2017 Nicolas Polomack
** Last update Thu Mar 30 02:23:04 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "raytracer.h"

sfColor		apply_effects(t_thread *t, t_obj *obj, float dist)
{
  sfColor	col;

  prepare_light_calc(t, obj, dist);
  col = calc_lights(t, obj);
  col = light_effects(t, obj, col);
  return (col);
}

void	prepare_light_ray(t_thread *t, int i)
{
  t->ray.dir.x = t->params->lights[i].pos.x - t->impact.x;
  t->ray.dir.y = t->params->lights[i].pos.y - t->impact.y;
  t->ray.dir.z = t->params->lights[i].pos.z - t->impact.z;
}

void		prepare_reflect(t_thread *t)
{
  float		norme;

  t->ray.orig = t->impact;
  t->normal = normalize(t->normal);
  t->ray.dir = normalize(t->ray.dir);
  norme = -dot(t->normal, t->ray.dir);
  t->ray.dir.x = t->ray.dir.x + (2.0F * t->normal.x * norme);
  t->ray.dir.y = t->ray.dir.y + (2.0F * t->normal.y * norme);
  t->ray.dir.z = t->ray.dir.z + (2.0F * t->normal.z * norme);
}

sfColor		apply_reflect(sfColor col, sfColor reflect, float ratio)
{
  col.r = ((float)reflect.r) * ratio +
    ((float)col.r) * (1.0F - ratio);
  col.g = ((float)reflect.g) * ratio +
    ((float)col.g) * (1.0F - ratio);
  col.b = ((float)reflect.b) * ratio +
    ((float)col.b) * (1.0F - ratio);
  return (col);
}

sfColor		light_effects(t_thread *t, t_obj *obj, sfColor col)
{
  if (t->depth++ < t->params->config.reflect_depth && obj->reflect > 0)
    {
      t->from = obj;
      t->ray.dir = t->dir;
      prepare_reflect(t);
      col = apply_reflect(col, raytrace(t), obj->reflect);
    }
  return (col);
}
