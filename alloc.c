/*
** alloc.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Mar 30 02:39:33 2017 Nicolas Polomack
** Last update	Sat May 27 22:18:59 2017 Full Name
*/

#include <stdlib.h>
#include "raytracer.h"
#include "sfcaster.h"
#include "my.h"
#include "bmp.h"

void	init_buffers_cli(t_window *w, t_params *params)
{
  params->config.bmp = (params->screen_size.x >= 8192 ||
			params->screen_size.y >= 8192);
  if (params->config.bmp && !params->config.clu_cli)
    my_printf("The requested image is too big to be printed %s%s",
	      "inside of a window.\n",
	      "Switching to buffer-only frame rendering.\n");
  w->buffer = assemble_texture(&w->texture, &w->sprite,
			       params->screen_size.x, params->screen_size.y);
  if (params->config.stereo)
    {
      if (params->config.bmp)
	w->buffer2 = my_framebuffer_create(params->screen_size.x,
					   params->screen_size.y);
      else
	w->buffer2 = assemble_texture(&w->texture2, &w->sprite2,
				      params->screen_size.x,
				      params->screen_size.y);
    }
  w->sizes = params->screen_size;
}

void	init_buffers(t_window *w, t_params *params)
{
  params->config.bmp = (params->screen_size.x >= 8192 ||
			params->screen_size.y >= 8192) ||
    !!params->config.clu_cli;
  if (params->config.bmp && !params->config.clu_cli)
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
				      params->screen_size.x,
				      params->screen_size.y);
    }
  w->sizes = params->screen_size;
}

void	prepare_objs(t_params *params)
{
  int	i;
  int	j;
  float	scale;

  i = -1;
  while (++i < params->nb_objs)
    if (params->objs[i].type == -1 && params->objs[i].obj_parse)
      {
	scale = params->objs[i].scale;
	j = -1;
	while (++j < params->objs[i].obj_parse->nb_poly)
	  {
	    params->objs[i].obj_parse->p1[j].x *= scale;
            params->objs[i].obj_parse->p1[j].y *= scale;
            params->objs[i].obj_parse->p1[j].z *= scale;
            params->objs[i].obj_parse->p2[j].x *= scale;
            params->objs[i].obj_parse->p2[j].y *= scale;
            params->objs[i].obj_parse->p2[j].z *= scale;
            params->objs[i].obj_parse->p3[j].x *= scale;
            params->objs[i].obj_parse->p3[j].y *= scale;
            params->objs[i].obj_parse->p3[j].z *= scale;
	  }
      }
}

void	save_buffers(t_window *w, t_params *params)
{
  save_bmp(w->buffer, "capture.bmp");
}
