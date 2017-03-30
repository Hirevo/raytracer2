/*
** thread.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Mar 28 16:22:29 2017 Nicolas Polomack
** Last update Thu Mar 30 12:10:38 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <pthread.h>
#include "raytracer.h"

void		*render_thread(void *arg)
{
  t_thread	*t;

  t = (t_thread *)arg;
  set_focal_dist(t);
  if (t->params->config.stereo)
    render_stereo_frame(t);
  else
    render_frame(t);
  return (NULL);
}

void	update_frame(t_window *w, pthread_mutex_t *mutex, int bmp)
{
  if (bmp || pthread_mutex_trylock(mutex) != 0)
    return ;
  sfTexture_updateFromPixels(w->texture, w->buffer->pixels,
                             w->buffer->width, w->buffer->height, 0, 0);
  sfRenderWindow_drawSprite(w->window, w->sprite, NULL);
  sfRenderWindow_display(w->window);
  pthread_mutex_unlock(mutex);
}

void	set_limits(t_thread *t, t_window *w,
		   t_params *params, int i)
{
  if (!(i % 2))
    {
      t->offs.x = (params->screen_size.x /
		   (params->t_count / 2)) * (i / 2);
      t->offs.y = 0;
    }
  else
    {
      t->offs.x = (params->screen_size.x /
		   (params->t_count / 2)) * ((i - 1) / 2);
      t->offs.y = (params->screen_size.y / 2);
    }
  t->end.x = (t->offs.x + (w->buffer->width /
			   (params->t_count / 2)));
  t->end.y = (t->offs.y + (w->buffer->height / 2));
  t->end.x += (i >= (params->t_count - 2)) ?
    params->screen_size.x % (params->t_count / 2) : 0;
}

int	init_thread(t_window *w, t_params *params)
{
  int		i;
  t_thread	*t;

  i = -1;
  params->t_count = get_core_count() * 2;
  params->t = malloc(sizeof(pthread_t) * params->t_count);
  pthread_mutex_init(&params->mutex, NULL);
  while (++i < params->t_count)
    {
      t = malloc(sizeof(t_thread));
      t->params = params;
      t->w = w;
      t->start = params->start;
      set_limits(t, w, params, i);
      pthread_create(&(params->t[i]), NULL, render_thread, (void *)t);
    }
  i = -1;
  while (++i < params->t_count)
    pthread_join(params->t[i], NULL);
  return (0);
}
