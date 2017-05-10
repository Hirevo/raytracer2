/*
** ssaa.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr  4 22:25:51 2017 Nicolas Polomack
** Last update Wed May 10 17:44:15 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <math.h>
#include "raytracer.h"

void	render_pixel(t_thread *t, sfVector2f v, int i, sfVector2f f)
{
  if (t->params->config.depth_rays > 1)
    t->ssaa_col[i] = dof(t, v.x, v.y);
  else
    {
      t->ray.orig = t->start;
      t->depth = 0;
      t->from = NULL;
      t->primary = 1;
      t->ray.dir = calc_dir_vector(t->params->screen_size,
				   v.x + f.x, v.y + f.y,
				   t->params->config.fov);
      rotation(&t->ray.dir, &t->params->r);
      t->ssaa_col[i] = raytrace(t);
    }
}

sfColor		ssaa(t_thread *t, float x, float y)
{
  float		ssaa_offs;
  int		i;
  sfVector2f	v;
  sfVector2f	f;

  i = 0;
  f.x = -0.5F;
  ssaa_offs = 1.0F /
    fmax((sqrtf((float)(t->params->config.ssaa)) -
	  1.0F), 1);
  while (f.x <= 0.5F)
    {
      f.y = -0.5F;
      while (f.y <= 0.5F)
        {
          v.x = x;
          v.y = y;
          render_pixel(t, v, i, f);
          i += 1;
          f.y += ssaa_offs;
        }
      f.x += ssaa_offs;
    }
  return (average_colors(t->ssaa_col,
			 t->params->config.ssaa));
}

void	render_ssaa(t_thread *t)
{
  if ((t->ssaa_col = malloc(sizeof(sfColor) *
			    t->params->config.ssaa)) == NULL)
    return ;
  t->screen_pos.x = t->offs.x - 1;
  while (++t->screen_pos.x < t->end.x)
    {
      t->screen_pos.y = t->offs.y - 1;
      while (++t->screen_pos.y < t->end.y)
        put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y,
		  ssaa(t, t->screen_pos.x, t->screen_pos.y));
      if (t->params->config.live)
	update_frame(t->w, &t->params->mutex, t->params->config.bmp);
    }
  free(t->ssaa_col);
}
