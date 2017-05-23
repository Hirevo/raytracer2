/*
** get_light_coef.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 20:54:49 2017 Nicolas Polomack
** Last update Tue May 23 23:06:05 2017 Arthur Knoepflin
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"

void	prepare_light_calc(t_thread *t, t_obj *obj, float dist)
{
  t->impact.x = t->ray.orig.x + t->ray.dir.x * dist;
  t->impact.y = t->ray.orig.y + t->ray.dir.y * dist;
  t->impact.z = t->ray.orig.z + t->ray.dir.z * dist;
  t->ray.orig = t->impact;
  t->normal = prepare(t->impact, obj, 1);
  if (obj->type != -1)
    t->params->get_normal[t->params->id[(int)obj->type]](t, obj);
  else
    t->normal = get_normal_obj(t, obj);
  t->normal = anti_prepare(t->normal, obj, 0);
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

sfColor		eval_luminosity(t_thread *t, sfColor col, float *coef)
{
  sfColor	ret;

  *coef = fmax(t->params->config.ambient,
	       get_light_coef(t->normal,
			      t->ray.dir));
  ret.r = ((float)col.r) * *coef;
  ret.g = ((float)col.g) * *coef;
  ret.b = ((float)col.b) * *coef;
  ret.a = 255;
  return (ret);
}

sfColor		calc_lights(t_thread *t, t_obj *obj, sfColor col)
{
  int		i;
  float		coef;
  sfColor	cols[t->params->nb_lights];

  i = -1;
  while (++i < t->params->nb_lights)
    if (t->params->config.shadow_rays > 1)
      cols[i] = diffuse_shadows(t, col, obj, i);
    else
      {
	prepare_light_ray(t, i);
	if (is_obstructed(t, obj))
	  cols[i] = get_shadow_color(t, col);
	else
	  {
	    cols[i] = eval_luminosity(t, col, &coef);
	    if (coef > 0.7)
	      cols[i] = specular_effect(cols[i], t, obj, i);
	  }
      }
  return (average_colors(cols, t->params->nb_lights));
}
