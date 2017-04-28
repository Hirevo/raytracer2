/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Fri Apr 28 14:27:31 2017 Nicolas Polomack
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

void	handle_events(t_window *w, t_params *params, sfEvent *event)
{
  static int i = 0;

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
	      update_frame(w, &params->mutex, params->config.bmp);
	    i = !i;
	  }
      if (sfKeyboard_isKeyPressed(sfKeyZ))
	params->start.x += 10;
      if (sfKeyboard_isKeyPressed(sfKeyS))
        params->start.x -= 10;
      if (sfKeyboard_isKeyPressed(sfKeyQ))
        params->start.y += 10;
      if (sfKeyboard_isKeyPressed(sfKeyD))
        params->start.y -= 10;
      if (sfKeyboard_isKeyPressed(sfKeyLShift))
        params->start.z -= 10;
      if (sfKeyboard_isKeyPressed(sfKeySpace))
        params->start.z += 10;
      if (sfKeyboard_isKeyPressed(sfKeyUp))
        params->r.y += 3;
      if (sfKeyboard_isKeyPressed(sfKeyDown))
        params->r.y -= 3;
      if (sfKeyboard_isKeyPressed(sfKeyLeft))
        params->r.z += 3;
      if (sfKeyboard_isKeyPressed(sfKeyRight))
        params->r.z -= 3;
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
      if (t->params->config.live)
	update_frame(t->w, &t->params->mutex, t->params->config.bmp);
    }
}

int		main(int ac, char **av, char **ae)
{
  t_window	w;
  sfEvent	event;
  t_params	params;

  if (ac < 2 || parse_args(&params, ac, av) == -1)
    return (84);
  if (params.help)
    return (disp_guide());
  params.seed = init_seed(ac, av, ae, (void *)&main);
  params.screen_size.x = 1920;
  params.screen_size.y = 1080;
<<<<<<< HEAD
  parse_from_file(&params, params.config.scene_file);
  /* init_room(&params); */
  /* init_reflect(&params); */
  /* init_test(&params); */
=======
  parse_from_file(&params, av[1]);
>>>>>>> 1e5561986d3f569b478c8a5329c5450042e66415
  if (load_libs(&params) == -1)
    return (84);
  init_buffers(&w, &params);
  clear_pixels(w.buffer);
  if (!params.config.bmp)
    create_window(&w.window, "Raytracer2", params.screen_size);
<<<<<<< HEAD
=======
  params.tesla_lvl = 40;
  init_thread(&w, &params);
  update_frame(&w, &params.mutex, params.config.bmp);
>>>>>>> 1e5561986d3f569b478c8a5329c5450042e66415
  while (!params.config.bmp && sfRenderWindow_isOpen(w.window))
    {
      init_thread(&w, &params);
      update_frame(&w, &params.mutex, params.config.bmp);
      handle_events(&w, &params, &event);
    }
  save_buffers(&w, &params);
  return (0);
}
