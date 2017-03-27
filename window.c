/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Mon Mar 27 03:15:36 2017 Nicolas Polomack
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

void	handle_events(t_window *w, sfEvent *event)
{
  if (sfWindow_hasFocus((sfWindow *)w->window))
    while (sfRenderWindow_pollEvent(w->window, event))
      if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	sfRenderWindow_close(w->window);
}

void	init(t_params *params)
{
  params->intersect[0] = intersect_sphere;
  params->intersect[1] = intersect_plane;
  params->intersect[2] = intersect_cyl;
  params->intersect[3] = intersect_cyl;
  params->intersect[4] = intersect_cone;
  params->intersect[5] = intersect_cone;
  params->intersect[6] = intersect_cone;
  params->get_normal[0] = get_normal_sphere;
  params->get_normal[1] = get_normal_plane;
  params->get_normal[2] = get_normal_cyl;
  params->get_normal[3] = get_normal_cyl;
  params->get_normal[4] = get_normal_cone;
  params->get_normal[5] = get_normal_cone;
  params->get_normal[6] = get_normal_cone;
  params->screen_pos.x = -1;
  params->screen_pos.y = -1;
  params->start.x = -200;
  params->start.y = 0;
  params->start.z = 0;
  params->nb_objs = 2;
  params->objs = malloc(sizeof(t_obj) * 2);
  params->objs[0].type = 3;
  params->objs[0].pos.x = 0;
  params->objs[0].pos.y = 0;
  params->objs[0].pos.z = 20;
  params->objs[0].rx = 0;
  params->objs[0].ry = 20;
  params->objs[0].rz = 20;
  params->objs[0].rad = 20;
  params->objs[0].height = 50;
  params->objs[0].col = get_sfcolor(255, 0, 0, 255);
  params->objs[1].type = 1;
  params->objs[1].pos.x = 0;
  params->objs[1].pos.y = 0;
  params->objs[1].pos.z = -25;
  params->objs[1].rx = 0;
  params->objs[1].ry = 0;
  params->objs[1].rz = 0;
  params->objs[1].col = get_sfcolor(0, 0, 255, 255);
  params->nb_lights = 1;
  params->lights = malloc(sizeof(t_light));
  params->lights[0].pos.x = -100;
  params->lights[0].pos.y = 50;
  params->lights[0].pos.z = 50;
  params->ambient = 0.05;
}

void	render_frame(t_window *w, t_params *params)
{
  while (++params->screen_pos.x < params->screen_size.x)
    {
      params->screen_pos.y = -1;
      while (++params->screen_pos.y < params->screen_size.y)
	{
	  params->ray.orig = params->start;
	  params->ray.dir = calc_dir_vector(params->screen_size,
					    params->screen_pos.x,
					    params->screen_pos.y, 105);
	  put_pixel(w->buffer, params->screen_pos.x, params->screen_pos.y,
		    raytrace(params));
	}
    }
}

int		main(int ac, char **av, char **ae)
{
  t_window	w;
  sfEvent	event;
  t_params	params;

  if (ac != 2)
    return (84);
  //if (!my_strcmp(av[1], "-h") || !my_strcmp(av[1], "--help"))
  //return (disp_guide());
  //params.seed = init_seed(ac, av, ae, (void *)&main);
  params.screen_size.x = 1280;
  params.screen_size.y = 720;
  create_window(&w.window, "raytracer2", params.screen_size);
  w.buffer = assemble_texture(&w.texture, &w.sprite,
			      params.screen_size.x, params.screen_size.y);
  init(&params);
  render_frame(&w, &params);
  sfTexture_updateFromPixels(w.texture, w.buffer->pixels,
			     w.buffer->width, w.buffer->height, 0, 0);
  sfRenderWindow_drawSprite(w.window, w.sprite, NULL);
  sfRenderWindow_display(w.window);
  while (sfRenderWindow_isOpen(w.window))
    handle_events(&w, &event);
  save_bmp(w.buffer, "capture.bmp");
  return (0);//free_all(&params, &w));
}
