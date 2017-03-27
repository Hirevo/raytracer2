/*
** get_light_coef.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 20:54:49 2017 Nicolas Polomack
** Last update Mon Mar 27 03:20:34 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"

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

int	is_obstructed(t_params *params, t_obj *obj)
{
  float	dist;
  int	i;

  i = -1;
  while (++i < params->nb_objs)
    {
      if (&(params->objs[i]) == obj)
        continue;
      dist = gather_dist(params, i);
      if (dist > 0 && dist < 1)
	return (1);
    }
  return (0);
}

sfColor		eval_luminosity(t_params *params, sfColor col)
{
  float		coef;
  sfColor	ret;

  coef = fmax(params->ambient,
              get_light_coef(params->normal,
                             params->ray.dir));
  ret.r = ((float)col.r) * coef;
  ret.g = ((float)col.g) * coef;
  ret.b = ((float)col.b) * coef;
  return (ret);
}
