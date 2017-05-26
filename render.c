/*
1;4803;0c** render.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Wed May 10 14:39:42 2017 Nicolas Polomack
** Last update	Thu May 25 21:58:07 2017 Full Name
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "my.h"

void	check_render(t_params *params, t_window *w)
{
  if (!params->config.stereo &&
      (params->config.ssaa == 1) &&
      params->config.tesla &&
      params->tesla_lvl > 1)
    {
      w->time_start = get_time();
      params->tesla_lvl -= 1;
      init_thread(w, params);
    }
  else if (!params->config.bmp)
    sfRenderWindow_setTitle(w->window, "Raytracer - Termine");
}

static int	increment_progress(t_window *w, t_params *params)
{
  static int	last = 0;

  w->progress += ((1.0F / ((float)w->sizes.x)) / 2.0F) * 100.0F;
  if (params->config.bmp)
    {
      if (((int)w->progress) != last)
        {
          pthread_mutex_lock(&params->mutex);
          last = w->progress;
          //my_printf("\rProgress: %d %%", last);
	  print_percent(last);
	  pthread_mutex_unlock(&params->mutex);
        }
      return (-1);
    }
  return (0);
}

static int	update_title(t_window *w, t_params *params)
{
  char		*final;

  if ((final = get_time_calc(w, my_int_to_char((int)w->progress))) == NULL
      || (final = my_fstrcat("Raytracer - ", final, 3)) == NULL)
    {
      pthread_mutex_unlock(&params->mutex);
      return (-1);
    }
  sfRenderWindow_setTitle(w->window, final);
  free(final);
  return (0);
}

void	update_progress(t_window *w, t_params *params)
{
  if (increment_progress(w, params) == -1 ||
      pthread_mutex_trylock(&params->mutex) != 0)
    return ;
  update_frame(w, params);
  if (update_title(w, params) == -1)
    return ;
  pthread_mutex_unlock(&params->mutex);
}
