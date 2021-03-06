/*
** teslation.c for teslation in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 28 11:08:45 2017 Arthur Knoepflin
** Last update Fri May 26 04:26:14 2017 Nicolas Polomack
*/

#include "raytracer.h"

static void	prepare_raytrace_tesla(t_thread *t, int x, int y)
{
  t->depth = 0;
  t->from = NULL;
  t->refr = 1;
  t->primary = 1;
  t->ray.dir = calc_dir_vector(t->params->screen_size,
			       x, y, t->params->config.fov);
  rotation(&t->ray.dir, &t->params->r);
}

static int	get_size_tesla(int lvl)
{
  int		i;
  int		size;

  size = 1;
  i = 0;
  while (i < lvl - 1)
    {
      size += 2;
      i += 1;
    }
  return (size);
}

static void	put_px_tesla(t_thread *t, sfVector2i pos,
			     int size_tesla, sfColor col)
{
  sfVector2i	put;

  put.y = 0;
  while (put.y < size_tesla)
    {
      put.x = 0;
      while (put.x < size_tesla)
  	{
	  put_pixel(t->w->buffer, t->offs.x + pos.x + put.x,
	  	    t->offs.y + pos.y + put.y, col);
    	  put.x += 1;
    	}
      put.y += 1;
    }
}

static void	raytrace_tesla(t_thread *t, int size_tesla, sfVector2i pos)
{
  if (t->params->config.depth_rays > 1)
    put_px_tesla(t, pos, size_tesla,
		 dof(t, t->offs.x + (pos.x + (size_tesla >> 1)),
		     t->offs.y + (pos.y + (size_tesla >> 1))));
  else
    {
      prepare_raytrace_tesla(t, t->offs.x + (pos.x + (size_tesla >> 1)),
			     t->offs.y + (pos.y + (size_tesla >> 1)));
      put_px_tesla(t, pos, size_tesla, raytrace(t));
    }
}

void		render_frame_tesla(t_thread *t)
{
  sfVector2i	pos;
  int		size_tesla;
  sfVector2i	size;

  size.x = t->end.x - t->offs.x;
  size.y = t->end.y - t->offs.y;
  size_tesla = get_size_tesla(t->tesla_lvl);
  pos.x = 0;
  while (pos.x < size.x)
    {
      pos.y = 0;
      while (pos.y < size.y)
	{
	  t->ray.orig = t->start;
	  raytrace_tesla(t, size_tesla, pos);
	  pos.y += size_tesla;
	}
      if (t->params->config.live || t->params->config.bmp)
	update_progress(t->w, t->params);
      pos.x += size_tesla;
    }
}
