/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Fri Mar 24 15:15:36 2017 Nicolas Polomack
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
  w.buffer = load_bmp("resources/loading.bmp", &w.sprite, &w.texture);
  sfTexture_updateFromPixels(w.texture, w.buffer->pixels,
			     w.buffer->width, w.buffer->height, 0, 0);
  sfRenderWindow_drawSprite(w.window, w.sprite, NULL);
  sfRenderWindow_display(w.window);
  while (sfRenderWindow_isOpen(w.window))
    handle_events(&w, &event);
  save_bmp(w.buffer, "capture.bmp");
  return (0);//free_all(&params, &w));
}
