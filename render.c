/*
** render.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Wed May 10 14:39:42 2017 Nicolas Polomack
** Last update	Thu May 25 21:58:07 2017 Full Name
*/

#include "raytracer.h"

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
