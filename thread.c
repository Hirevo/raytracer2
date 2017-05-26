/*
** thread.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Mar 28 16:22:29 2017 Nicolas Polomack
** Last update Fri May 26 03:45:32 2017 Nicolas Polomack
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

void	update_frame(t_window *w, t_params *params)
{
  if (!params->config.bmp)
    {
      sfTexture_updateFromPixels(w->texture, w->buffer->pixels,
				 w->buffer->width, w->buffer->height, 0, 0);
      sfRenderWindow_drawSprite(w->window, w->sprite, NULL);
      sfRenderWindow_display(w->window);
    }
}

static void	set_limits(t_thread *t, t_window *w,
			   t_params *params, int i)
{
  sfVector2i	size;

  size.x = params->config.end.x - params->config.offs.x;
  size.y = params->config.end.y - params->config.offs.y;
  if (!(i % 2))
    {
      t->offs.x = (size.x / (params->t_count / 2)) * (i / 2);
      t->offs.y = params->config.offs.y;
    }
  else
    {
      t->offs.x = (size.x / (params->t_count / 2)) * ((i - 1) / 2);
      t->offs.y = params->config.offs.y + (size.y / 2);
    }
  t->end.x = (t->offs.x + (size.x / (params->t_count / 2)));
  t->end.y = (t->offs.y + (size.y / 2));
  t->end.x += (i >= (params->t_count - 2)) ?
    size.x % (params->t_count / 2) : 0;
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
  if ((params->t = malloc(sizeof(pthread_t) * params->t_count)) == NULL)
    return (-1);
  w->progress = 0;
  if (params->config.bmp)
    my_printf("\nProgress: 0 %%");
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
