/*
** merge.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Mar 29 21:40:26 2017 Nicolas Polomack
** Last update Thu Mar 30 13:57:15 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdarg.h>
#include "raytracer.h"
#include "sfcaster.h"

sfColor		add_colors(sfColor *col, int nb_l)
{
  sfColor	final;
  int		rgb[3];
  int		i;

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  i = -1;
  while (++i < nb_l)
    {
      rgb[0] += col[i].r;
      rgb[1] += col[i].g;
      rgb[2] += col[i].b;
    }
  final.r = fmin(255, rgb[0]);
  final.g = fmin(255, rgb[1]);
  final.b = fmin(255, rgb[2]);
  final.a = 255;
  return (final);
}

sfColor		extract_color(t_my_framebuffer *buffer,
			      int x, int y)
{
  sfColor	col;

  col.r = buffer->pixels[(buffer->width * y + x) * 4];
  col.g = buffer->pixels[(buffer->width * y + x) * 4 + 1];
  col.b = buffer->pixels[(buffer->width * y + x) * 4 + 2];
  col.a = buffer->pixels[(buffer->width * y + x) * 4 + 3];
  return (col);
}

static void		fill_buffer(int count, t_my_framebuffer *ret,
				    t_my_framebuffer **buffers)
{
  int		i;
  int		j;
  int		c;
  sfColor	cols[count];

  i = -1;
  while (++i < ret->width)
    {
      j = -1;
      while (++j < ret->height)
        {
          c = -1;
          while (++c < count)
            cols[c] = extract_color(buffers[c], i, j);
          put_pixel(ret, i, j, add_colors(cols, count));
        }
    }
}

t_my_framebuffer	*merge_buffers(int count, ...)
{
  int			i;
  va_list		ap;
  t_my_framebuffer      *buffers[count];
  t_my_framebuffer	*ret;

  va_start(ap, count);
  i = -1;
  while (++i < count)
    buffers[i] = va_arg(ap, t_my_framebuffer *);
  va_end(ap);
  if ((ret = my_framebuffer_create(buffers[0]->width,
				   buffers[0]->height)) == NULL)
    return (NULL);
  fill_buffer(count, ret, buffers);
  return (ret);
}
