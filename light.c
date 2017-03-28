/*
** get_light_coef.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 20:54:49 2017 Nicolas Polomack
** Last update Tue Mar 28 20:45:10 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"

sfColor		get_shadow_color(t_thread *t, t_obj *obj)
{
  float		coef;
  sfColor	ret;

  coef = t->params->ambient;
  ret.r = ((float)obj->col.r) * coef;
  ret.g = ((float)obj->col.g) * coef;
  ret.b = ((float)obj->col.b) * coef;
  ret.a = 255;
  return (ret);
}

float	get_light_coef(sfVector3f light, sfVector3f imp)
{
  float	coef;

  coef = norm(light);
  if (coef == 0)
    return (0);
  light.x /= coef;
  light.y /= coef;
  light.z /= coef;
  coef = norm(imp);
  if (coef == 0)
    return (0);
  imp.x /= coef;
  imp.y /= coef;
  imp.z /= coef;
  coef = dot(light, imp);
  if (coef < 0)
    coef = 0;
  return (coef);
}

int	is_obstructed(t_thread *t, t_obj *obj)
{
  float	dist;
  int	i;

  i = -1;
  while (++i < t->params->nb_objs)
    {
      if (&(t->params->objs[i]) == obj)
        continue;
      dist = gather_dist(t, i);
      if (dist > 0 && dist < 1)
	return (1);
    }
  return (0);
}

sfColor		eval_luminosity(t_thread *t, sfColor col)
{
  float		coef;
  sfColor	ret;

  coef = fmax(t->params->ambient,
              get_light_coef(t->normal,
                             t->ray.dir));
  ret.r = ((float)col.r) * coef;
  ret.g = ((float)col.g) * coef;
  ret.b = ((float)col.b) * coef;
  ret.a = 255;
  return (ret);
}

sfColor		calc_lights(t_thread *t, t_obj *obj)
{
  int		i;
  sfColor	cols[t->params->nb_lights];

  i = -1;
  while (++i < t->params->nb_lights)
    {
      prepare_light_ray(t, i);
      if (is_obstructed(t, obj))
        cols[i] = get_shadow_color(t, obj);
      else
        cols[i] = eval_luminosity(t, obj->col);
    }
  return (average_colors(cols, t->params->nb_lights));
}
