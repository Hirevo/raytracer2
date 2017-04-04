/*
** depth.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2/depth_of_field
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 19:58:36 2017 Nicolas Polomack
** Last update Tue Apr  4 22:04:56 2017 Nicolas Polomack
*/

#include <float.h>
#include <limits.h>
#include "raytracer.h"

void		calc_focal_vector(t_thread *t, float x, float y)
{
  sfVector3f	aim;
  float		dx;
  float		dy;

  t->ray.orig = t->start;
  t->ray.dir = calc_dir_vector(t->params->screen_size,
                               x, y, t->params->config.fov);
  rotation(&t->ray.dir, &t->params->r);
  aim.x = t->ray.orig.x + t->ray.dir.x * t->focal_dist;
  aim.y = t->ray.orig.y + t->ray.dir.y * t->focal_dist;
  aim.z = t->ray.orig.z + t->ray.dir.z * t->focal_dist;
  dx = ((float)my_rand(t->params->seed)) / (((float)(INT_MAX) + 1.0F));
  dy = ((float)my_rand(t->params->seed)) / (((float)(INT_MAX) + 1.0F));
  t->ray.orig.y += 3.0F * dx;
  t->ray.orig.z += 3.0F * dy;
  t->ray.dir.x = aim.x - t->ray.orig.x;
  t->ray.dir.y = aim.y - t->ray.orig.y;
  t->ray.dir.z = aim.z - t->ray.orig.z;
}

sfColor		dof(t_thread *t, float x, float y)
{
  float		i;
  float		j;
  sfColor	col;

  i = -1;
  while (++i < t->params->config.depth_rays)
    {
      j = -1;
      while (++j < t->params->config.depth_rays)
        {
	  t->depth = 0;
	  t->from = NULL;
          calc_focal_vector(t, x + (j / t->params->config.depth_rays),
                            y + (i / t->params->config.depth_rays));
          t->depth_col[(int)((i * t->params->config.depth_rays) + j)] =
            raytrace(t);
        }
    }
  col = average_colors(t->depth_col,
		       t->params->config.depth_rays *
		       t->params->config.depth_rays);
  return (col);
}
