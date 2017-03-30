/*
** alloc.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:39:33 2017 Nicolas Polomack
** Last update Thu Mar 30 13:50:48 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "raytracer.h"
#include "sfcaster.h"
#include "my.h"
#include "bmp.h"

void	init_buffers(t_window *w, t_params *params)
{
  params->config.bmp = (params->screen_size.x >= 8192 ||
			params->screen_size.y >= 8192);
  if (params->config.bmp)
    my_printf("The requested image is too big to be printed %s%s",
	      "inside of a window.\n",
	      "Switching to buffer-only frame rendering.\n");
  if (params->config.bmp)
    w->buffer = my_framebuffer_create(params->screen_size.x,
				      params->screen_size.y);
  else
    w->buffer = assemble_texture(&w->texture, &w->sprite,
				 params->screen_size.x, params->screen_size.y);
  if (params->config.stereo)
    {
      if (params->config.bmp)
	w->buffer2 = my_framebuffer_create(params->screen_size.x,
					   params->screen_size.y);
      else
	w->buffer2 = assemble_texture(&w->texture2, &w->sprite2,
				      params->screen_size.x, params->screen_size.y);
    }
}

void	save_buffers(t_window *w, t_params *params)
{
  save_bmp(w->buffer, "capture.bmp");
  if (params->config.stereo)
    {
      save_bmp(w->buffer2, "capture2.bmp");
      save_bmp(merge_buffers(2, w->buffer, w->buffer2), "merge.bmp");
    }
}
