/*
** bmp.c for wolf3d in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Dec 21 19:31:11 2016 Nicolas Polomack
** Last update Sun May 28 18:01:33 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "raytracer.h"
#include "my.h"
#include "bmp.h"
#include "sfcaster.h"

t_my_framebuffer	*load_bmp(char *filename, sfSprite **spr,
				  sfTexture **tex)
{
  int			fd;
  t_bmp_header		head;
  t_bmp_info_header	info;
  t_my_framebuffer	*buffer;

  my_printf("Loading: %s...", filename);
  if ((fd = open(filename, O_RDONLY)) == -1 && my_printf(" Failed\n"))
    return (NULL);
  read(fd, &head, sizeof(t_bmp_header));
  read(fd, &info, sizeof(t_bmp_info_header));
  if (spr == NULL || tex == NULL)
    buffer = my_framebuffer_create(info.width, info.height);
  else
    buffer = assemble_texture(tex, spr, info.width, info.height);
  if (buffer == NULL && my_printf(" Failed\n"))
    return (NULL);
  read(fd, &head, head.off_bits -
       sizeof(t_bmp_header) - sizeof(t_bmp_info_header));
  read_pixel_buffer(buffer, fd,
		    info.bits_per_pixels, get_pad(info.width));
  close(fd);
  if (spr != NULL && tex != NULL)
    sfTexture_updateFromPixels(*tex, buffer->pixels,
			       buffer->width, buffer->height, 0, 0);
  return ((my_printf(" Ok!\n")) ? buffer : buffer);
}

void		read_pixel_buffer(t_my_framebuffer *buffer,
				  int fd, unsigned short bpp, int pad)
{
  sfVector2i	pos;
  int		trash;

  pos.y = buffer->height - 1;
  while (pos.y >= 0)
    {
      pos.x = -1;
      while (++(pos.x) < buffer->width)
	put_pixel(buffer, pos.x, pos.y, get_bmp_color(fd, bpp));
      read(fd, &trash, pad);
      pos.y -= 1;
    }
}

sfColor		get_bmp_color(int fd, unsigned short bpp)
{
  sfColor	color;
  unsigned char	t;

  if (bpp == 32)
    {
      read(fd, &t, sizeof(unsigned char));
      color.a = (int)t;
    }
  else
    color.a = 255;
  read(fd, &t, sizeof(unsigned char));
  color.b = (int)t;
  read(fd, &t, sizeof(unsigned char));
  color.g = (int)t;
  read(fd, &t, sizeof(unsigned char));
  color.r = (int)t;
  return (color);
}

int	get_pad(int w)
{
  int	i;

  i = 0;
  while (((w + i) % 4) != 0)
    i += 1;
  return (i);
}
