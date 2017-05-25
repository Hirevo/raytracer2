/*
** client_calc.c for calc in /home/Maxime/delivery/MUL/raytracer2/cluster/calculation/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May 25 10:03:57 2017 Maxime Jenny
** Last update	Thu May 25 10:10:42 2017 Full Name
*/

#include <stdlib.h>
#include <pthread.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "my.h"
#include "raytracer.h"

void		initialize_calculation(t_params *params, t_window *w,
				       sfVector2i *zone)
{
  int		i;
  t_thread	*t;

  i = 0;
  params->t_count = get_core_count() * 2;
  params->t = malloc(sizeof(pthread_t) * params->t_count);
  pthread_mutex_init(&params->mutex, NULL);
  while (i < params->t_count)
    {
      // if ((t = prepare_thread(w, params, i)) == NULL)
      // return (-1);
      // set_limits(t, w, params, i);
      // pthread_create(&(params->t[i]), NULL, render_thread, (void *)t);
      i++;
    }
  i = 0;
  while (++i < params->t_count)
    pthread_join(params->t[i++], NULL);
  check_render(params, w);
  return (0);
}
