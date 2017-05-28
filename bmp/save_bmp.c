/*
** load_bmp.c for wolf3d in 
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Jan  6 19:15:36 2017 Nicolas Polomack
** Last update Sun May 28 15:12:19 2017 Nicolas Polomack
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

void			save_bmp(t_my_framebuffer *buffer, char *name)
{
  int			fd;
  t_bmp_header		head;
  t_bmp_info_header	info;
  unsigned char		*p_buffer;
  int			pad;

  my_printf("Saving buffer into %s...", name);
  pad = calculate_pad(buffer);
  if ((p_buffer = malloc(sizeof (unsigned char) *
			 (buffer->width * buffer->height * 3 +
			  pad * buffer->height))) == NULL ||
      (fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return ;
  head = set_header(head, buffer, pad);
  write(fd, &head, 14);
  info = set_info(info, buffer, pad);
  write(fd, &info, 40);
  write_pixel_buffer(buffer, fd, p_buffer, pad);
  free(p_buffer);
  close(fd);
  my_printf(" Finished !\n");
}

int	calculate_pad(t_my_framebuffer *buffer)
{
  int	pad;

  pad = 0;
  while ((((buffer->width * 3) + pad) % 4) != 0)
    pad += 1;
  return (pad);
}

t_bmp_header	set_header(t_bmp_header head,
			   t_my_framebuffer *buffer, int pad)
{
  head.type = 0x4D42;
  head.size = 54 + (buffer->width * buffer->height * 3 +
		    pad * buffer->height);
  head.reserved1 = 0;
  head.reserved2 = 0;
  head.off_bits = 54;
  return (head);
}

t_bmp_info_header	set_info(t_bmp_info_header info,
			 t_my_framebuffer *buffer, int pad)
{
  info.size = 40;
  info.width = buffer->width;
  info.height = buffer->height;
  info.planes = 1;
  info.bits_per_pixels = 24;
  info.compression = 0;
  info.size_image = (buffer->width * buffer->height * 3 +
		     pad * buffer->height);
  info.xppm = 0;
  info.yppm = 0;
  info.clr_used = 0;
  info.clr_important = 0;
  return (info);
}

void		write_pixel_buffer(t_my_framebuffer *buffer,
                                   int fd, unsigned char *p_buffer, int pad)
{
  sfVector2i	pos;
  sfVector2i	buf;
  int		c;

  buf.y = 0;
  pos.y = buffer->height;
  while (--(pos.y) >= 0)
    {
      buf.x = 0;
      pos.x = -1;
      while (++(pos.x) < buffer->width)
        {
	  c = 3;
	  while (c--)
	    p_buffer[((buffer->width * 3) + pad) * buf.y + buf.x++] =
	      (unsigned char)(buffer->pixels[((buffer->width * pos.y
					       + pos.x) * 4) + c]);
        }
      c = pad;
      while (c--)
	p_buffer[((buffer->width * 3) + pad) * buf.y + buf.x++] = 0;
      buf.y += 1;
    }
  write(fd, p_buffer, sizeof(unsigned char) *
	(buffer->width * buffer->height * 3 + buffer->height * pad));
}
