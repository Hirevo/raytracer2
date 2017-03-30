/*
** alloc.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:39:33 2017 Nicolas Polomack
** Last update Thu Mar 30 02:46:11 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "raytracer.h"
#include "sfcaster.h"
#include "bmp.h"

void	init_buffers(t_window *w, t_params *params)
{
  w->buffer = assemble_texture(&w->texture, &w->sprite,
                              params->screen_size.x, params->screen_size.y);
  if (params->config.stereo)
    w->buffer2 = assemble_texture(&w->texture2, &w->sprite2,
                                 params->screen_size.x, params->screen_size.y);
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
