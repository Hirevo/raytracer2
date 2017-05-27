/*
** client_calc.c for calc in /home/Maxime/delivery/MUL/raytracer2/cluster/calculation/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May 25 10:03:57 2017 Maxime Jenny
** Last update	Sat May 27 19:39:38 2017 Full Name
*/

#include <stdlib.h>
#include <pthread.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "my.h"
#include "raytracer.h"
#include "server.h"
#include "sfcaster.h"

int		initialize_calculation(t_params *p, t_window *w,
				       t_zone *zone)
{
  int		i;
  sfEvent	event;
  t_thread	*t;

  i = 0;
  p->config.offs.x = zone->s_x;
  p->config.offs.y = zone->s_y;
  p->config.end.x = zone->e_x;
  p->config.end.y = zone->e_y;
  w->sizes.x = p->config.end.x - p->config.offs.x;
  w->sizes.y = p->config.end.y - p->config.offs.y;
  if (p->config.live)
    create_window(&w->window, "Raytracer2 - Client", p->screen_size);
  if ((init_thread(w, p)) == -1)
    return (-1);
  return (0);
}
