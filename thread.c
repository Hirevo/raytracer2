/*
** thread.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Mar 28 16:22:29 2017 Nicolas Polomack
** Last update	Thu May 25 00:45:33 2017 Full Name
*/

#include <stdlib.h>
#include <pthread.h>
#include "my.h"
#include "raytracer.h"

static void	*render_thread(void *arg)
{
  t_thread	*t;

  t = (t_thread *)arg;
  set_focal_dist(t);
  /* if (1) */
  /*   render_obj(t); */
  if (t->params->config.stereo)
    render_stereo_frame(t);
  else if (t->params->config.ssaa > 1)
    render_ssaa(t);
  else if (t->params->config.tesla)
    render_frame_tesla(t);
  else
    render_frame(t);
  return (NULL);
}

void	update_frame(t_window *w, pthread_mutex_t *mutex, int bmp)
{
  char	*time;
  char	*final;

  w->progress += ((1.0F / ((float)w->sizes.x)) / 2.0F) * 100.0F;
  if (bmp || pthread_mutex_trylock(mutex) != 0)
    return ;
  sfRenderWindow_display(w->window);
  sfTexture_updateFromPixels(w->texture, w->buffer->pixels,
			     w->buffer->width, w->buffer->height, 0, 0);
  sfRenderWindow_drawSprite(w->window, w->sprite, NULL);
  if ((time = get_time_calc(w, my_int_to_char((int)w->progress))) == NULL)
    {
      pthread_mutex_unlock(mutex);
      return ;
    }
  if ((final = my_fstrcat("Raytracer - ", time, 3)) == NULL)
    {
      pthread_mutex_unlock(mutex);
      return ;
    }
  sfRenderWindow_setTitle(w->window, final);
  free(final);
  pthread_mutex_unlock(mutex);
}

static void	set_limits(t_thread *t, t_window *w,
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

static t_thread	*prepare_thread(t_window *w, t_params *params, int i)
{
  t_thread	*t;

  if ((t = malloc(sizeof(t_thread))) == NULL)
    return (NULL);
  t->params = params;
  t->w = w;
  t->id = i;
  t->tesla_lvl = params->tesla_lvl;
  t->start = params->start;
  if ((t->depth_col = malloc(sizeof(sfColor) *
			     t->params->config.depth_rays *
			     t->params->config.depth_rays)) == NULL)
    return (NULL);
  return (t);
}

int		init_thread(t_window *w, t_params *params)
{
  int		i;
  t_thread	*t;

  i = -1;
  params->t_count = get_core_count() * 2;
  params->t = malloc(sizeof(pthread_t) * params->t_count);
  w->progress = 0;
  pthread_mutex_init(&params->mutex, NULL);
  while (++i < params->t_count)
    {
      if ((t = prepare_thread(w, params, i)) == NULL)
	return (-1);
      set_limits(t, w, params, i);
      pthread_create(&(params->t[i]), NULL, render_thread, (void *)t);
    }
  i = -1;
  while (++i < params->t_count)
    pthread_join(params->t[i], NULL);
  check_render(params, w);
  return (0);
}
