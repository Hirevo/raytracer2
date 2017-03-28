/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Wed Mar 29 01:36:45 2017 Nicolas Polomack
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

void	handle_events(t_window *w, t_params *params,sfEvent *event)
{
  if (sfWindow_hasFocus((sfWindow *)w->window))
    {
      while (sfRenderWindow_pollEvent(w->window, event))
	if ((event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	    || event->type == sfEvtClosed)
	  sfRenderWindow_close(w->window);
      if (sfKeyboard_isKeyPressed(sfKeyZ))
	params->start.x += 3;
      if (sfKeyboard_isKeyPressed(sfKeyS))
	params->start.x -= 3;
      if (sfKeyboard_isKeyPressed(sfKeyQ))
	params->start.y += 3;
      if (sfKeyboard_isKeyPressed(sfKeyD))
	params->start.y -= 3;
      if (sfKeyboard_isKeyPressed(sfKeySpace))
	params->start.z += 3;
      if (sfKeyboard_isKeyPressed(sfKeyLShift))
	params->start.z -= 3;
    }
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
  params->start.x = -150;
  params->start.y = 0;
  params->start.z = 20;
  params->nb_objs = 5;
  params->objs = malloc(sizeof(t_obj) * 5);
  my_memset((char *)params->objs, 0, sizeof(t_obj) * 5);
  params->objs[0].type = 0;
  params->objs[0].pos.x = -10;
  params->objs[0].pos.y = 55;
  params->objs[0].pos.z = 20;
  params->objs[0].rx = 0;
  params->objs[0].ry = 0;
  params->objs[0].rz = 0;
  params->objs[0].rad = 25;
  params->objs[0].reflect = 0.5;
  params->objs[0].spec_coef = 50;
  params->objs[0].col = get_sfcolor(0, 255, 0, 255);
  params->objs[1].type = 0;
  params->objs[1].pos.x = -10;
  params->objs[1].pos.y = 0;
  params->objs[1].pos.z = 20;
  params->objs[1].rx = 0;
  params->objs[1].ry = 0;
  params->objs[1].rz = 0;
  params->objs[1].rad = 25;
  params->objs[1].reflect = 0.5;
  params->objs[1].spec_coef = 50;
  params->objs[1].col = get_sfcolor(255, 0, 0, 255);
  params->objs[2].type = 0;
  params->objs[2].pos.x = -10;
  params->objs[2].pos.y = -55;
  params->objs[2].pos.z = 20;
  params->objs[2].rx = 0;
  params->objs[2].ry = 0;
  params->objs[2].rz = 0;
  params->objs[2].rad = 25;
  params->objs[2].reflect = 0.5;
  params->objs[2].spec_coef = 50;
  params->objs[2].col = get_sfcolor(0, 0, 255, 255);
  params->objs[3].type = 1;
  params->objs[3].pos.x = 30;
  params->objs[3].pos.y = 0;
  params->objs[3].pos.z = 0;
  params->objs[3].rx = 0;
  params->objs[3].ry = -90;
  params->objs[3].rz = 0;
  params->objs[3].rad = 20;
  params->objs[3].aper = 20;
  params->objs[3].height = 50;
  params->objs[3].reflect = 0;
  params->objs[3].spec_coef = 20;
  params->objs[3].col = get_sfcolor(100, 100, 100, 255);
  params->objs[4].type = 1;
  params->objs[4].pos.x = 0;
  params->objs[4].pos.y = 0;
  params->objs[4].pos.z = -25;
  params->objs[4].rx = 0;
  params->objs[4].ry = 0;
  params->objs[4].rz = 0;
  params->objs[4].reflect = 0;
  params->objs[4].spec_coef = 20;
  params->objs[4].col = get_sfcolor(100, 100, 100, 255);
  params->nb_lights = 1;
  params->lights = malloc(sizeof(t_light) * 1);
  params->lights[0].pos.x = 0;
  params->lights[0].pos.y = 0;
  params->lights[0].pos.z = 100;
  params->ambient = 0;
  params->reflect_depth = 3;
}

void	render_frame(t_thread *t)
{
  t->screen_pos.x = t->offs.x - 1;
  while (++t->screen_pos.x < t->end.x)
    {
      t->screen_pos.y = t->offs.y - 1;
      while (++t->screen_pos.y < t->end.y)
	{
	  t->ray.orig = t->start;
	  t->depth = 0;
	  t->from = NULL;
	  t->ray.dir = calc_dir_vector(t->params->screen_size,
				       t->screen_pos.x,
				       t->screen_pos.y, 104);
	  put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y,
		    raytrace(t));
	}
      //update_frame(t->w, &t->params->mutex);
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
  create_window(&w.window, "Raytracer2", params.screen_size);
  w.buffer = assemble_texture(&w.texture, &w.sprite,
			      params.screen_size.x, params.screen_size.y);
  init(&params);
  init_thread(&w, &params);
  update_frame(&w, &params.mutex);
  while (sfRenderWindow_isOpen(w.window))
    {
      handle_events(&w, &params, &event);
    }
  save_bmp(w.buffer, "capture.bmp");
  return (0);//free_all(&params, &w));
}
