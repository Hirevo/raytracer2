/*
** sfcaster.c for sfcaster.c in /home/nicolaspolomack/mylibcsfml/
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Nov 18 18:50:32 2016 Nicolas Polomack
** Last update Fri Feb 17 17:32:18 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "sfcaster.h"

t_my_framebuffer	*my_framebuffer_create(int width, int height)
{
  sfUint8		*pixels;
  t_my_framebuffer	*framebuffer;
  int			i;

  framebuffer = malloc(sizeof(t_my_framebuffer));
  pixels = malloc(sizeof(sfUint8) * width * height * 4);
  if (pixels == NULL || framebuffer == NULL)
    return (NULL);
  framebuffer->pixels = pixels;
  framebuffer->width = width;
  framebuffer->height = height;
  i = 0;
  while (i < (width * height * 4))
    {
      pixels[i] = 0;
      i = i + 1;
    }
  return (framebuffer);
}

void	clear_pixels(t_my_framebuffer *buffer)
{
  int	i;

  i = 0;
  while (i < (buffer->width * buffer->height * 4))
    {
      buffer->pixels[i] = (!((i + 1) % 4)) ? 255 : 0;
      i = i + 1;
    }
}
