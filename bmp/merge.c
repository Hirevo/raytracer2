/*
** merge.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Mar 29 21:40:26 2017 Nicolas Polomack
** Last update Wed Mar 29 22:32:08 2017 Nicolas Polomack
*/

#include <stdarg.h>
#include "raytracer.h"
#include "sfcaster.h"

sfColor		extract_color(t_my_framebuffer *buffer, int x, int y)
{
  sfColor	col;

  col.r = buffer->pixels[(buffer->width * y + x) * 4];
  col.g = buffer->pixels[(buffer->width * y + x) * 4 + 1];
  col.b = buffer->pixels[(buffer->width * y + x) * 4 + 2];
  col.a = buffer->pixels[(buffer->width * y + x) * 4 + 3];
  return (col);
}

t_my_framebuffer	*merge_buffers(int count, ...)
{
  int			ijc[3];
  va_list		ap;
  sfColor		cols[count];
  t_my_framebuffer      *buffers[count];
  t_my_framebuffer	*ret;

  va_start(ap, count);
  ijc[2] = -1;
  while (++(ijc[2]) < count)
    buffers[ijc[2]] = va_arg(ap, t_my_framebuffer *);
  va_end(ap);
  if ((ret = my_framebuffer_create(buffers[0]->width, buffers[0]->height)) == NULL)
    return (NULL);
  ijc[0] = -1;
  while (++(ijc[0]) < ret->width)
    {
      ijc[1] = -1;
      while (++(ijc[1]) < ret->height)
	{
	  ijc[2] = -1;
	  while (++(ijc[2]) < count)
	    cols[ijc[2]] = extract_color(buffers[ijc[2]], ijc[0], ijc[1]);
	  put_pixel(ret, ijc[0], ijc[1], average_colors(cols, count));
	}
    }
  return (ret);
}
