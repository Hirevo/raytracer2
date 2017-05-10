/*
** diffuse.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Apr 28 11:07:58 2017 Nicolas Polomack
** Last update Wed May 10 14:27:34 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

sfVector3f	get_shadow_ray(t_thread *t, int i)
{
  sfVector3f	to_light;

  to_light = t->params->lights[i].pos;
  to_light.x = (to_light.x + ((t->params->config.shadow_rays > 1 &&
			       t->primary == 1) ?
			      ((fmodf((float)my_rand(t->params->seed),
				      100.0F)) / 10.0F) : 0)) - t->impact.x;
  to_light.y = (to_light.y + ((t->params->config.shadow_rays > 1 &&
			       t->primary == 1) ?
			      ((fmodf((float)my_rand(t->params->seed),
				      100.0F)) / 10.0F) : 0)) - t->impact.y;
  to_light.z = to_light.z - t->impact.z;
  return (to_light);
}

sfColor		diffuse_shadows(t_thread *t, sfColor col,
				t_obj *obj, int i)
{
  sfColor	cols[t->params->config.shadow_rays];
  float		coef;
  int		x;
  sfVector3f	imp;

  x = 0;
  imp = t->impact;
  while ((t->primary && x < t->params->config.shadow_rays) ||
	 (!t->primary && !x))
    {
      t->impact = imp;
      t->ray.dir = get_shadow_ray(t, i);
      if (is_obstructed(t, obj))
	cols[x] = get_shadow_color(t, col);
      else
	{
	  cols[x] = eval_luminosity(t, col, &coef);
	  if (coef > 0)
	    cols[x] = specular_effect(cols[i], t, obj, i);
	}
      x += 1;
    }
  return (average_colors(cols, t->params->config.shadow_rays));
}
