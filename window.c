/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Fri May 26 03:47:00 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <pthread.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sfcaster.h"
#include "raytracer.h"
#include "server.h"
#include "bmp.h"
#include "my.h"

int		create_window(sfRenderWindow **w, char *name,
			      sfVector2i screen_size)
{
  sfVideoMode	mode;

  mode.width = screen_size.x;
  mode.height = screen_size.y;
  mode.bitsPerPixel = 32;
  *w = sfRenderWindow_create(mode, name, sfClose, NULL);
  if (*w == NULL)
    return (-1);
  return (0);
}

void		handle_events(t_window *w, t_params *params, sfEvent *event)
{
  static int	i = 0;

  if (sfWindow_hasFocus((sfWindow *)w->window))
    {
      while (sfRenderWindow_pollEvent(w->window, event))
	if ((event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	    || event->type == sfEvtClosed)
	  sfRenderWindow_close(w->window);
	else if (params->config.stereo &&
		 event->type == sfEvtKeyPressed && event->key.code == sfKeyT)
	  {
	    if (!i)
	      {
		sfTexture_updateFromPixels(w->texture2, w->buffer2->pixels,
					   w->buffer->width, w->buffer->height, 0, 0);
		sfRenderWindow_drawSprite(w->window, w->sprite2, NULL);
		sfRenderWindow_display(w->window);
	      }
	    else
	      update_frame(w, params);
	    i = !i;
	  }
      check_keys(params);
    }
}

void	render_frame(t_thread *t)
{
  t->screen_pos.x = t->offs.x - 1;
  while (++t->screen_pos.x < t->end.x)
    {
      t->screen_pos.y = t->offs.y - 1;
      while (++t->screen_pos.y < t->end.y)
	if (t->params->config.depth_rays > 1)
	  put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y,
		    dof(t, t->screen_pos.x, t->screen_pos.y));
	else
	  {
	    t->ray.orig = t->start;
	    prepare_raytrace(t);
	    put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y,
		      raytrace(t));
	  }
      if (t->params->config.live || t->params->config.bmp)
	update_progress(t->w, t->params);
    }
}

static int	prepare_render(t_params *params, t_window *w)
{
  if (parse_from_file(params, params->config.scene_file))
    return (84);
  if (load_libs(params) == -1)
    return (84);
  if (!params->config.clu_cli)
    {
      params->config.offs.x = 0;
      params->config.offs.y = 0;
      params->config.end = params->screen_size;
      w->sizes = params->screen_size;
    }
  init_buffers(w, params);
  prepare_objs(params);
  clear_pixels(w->buffer);
  w->time_start = get_time();
  return (0);
}

int		main(int ac, char **av, char **ae)
{
  t_window	w;
  sfEvent	event;
  t_params	params;

  if (ac < 2 || parse_args(&params, ac, av) == -1)
    return (84);
  if (ac == 1 || params.help)
    return (disp_guide());
  if (prepare_render(&params, &w) == 84)
    return (84);
  if (params.config.clu_serv == 1)
    return (server_cluster(&w, &params));
  if (params.config.clu_cli)
    return (client_cluster(&params, &w));
  if (!params.config.bmp)
    create_window(&w.window, "Raytracer2", params.screen_size);
  w.time_start = get_time();
  init_thread(&w, &params);
  if (params.config.bmp)
    my_putchar(012);
  update_frame(&w, &params);
  while (!params.config.bmp && sfRenderWindow_isOpen(w.window))
    handle_events(&w, &params, &event);
  save_buffers(&w, &params);
  return (0);
}
