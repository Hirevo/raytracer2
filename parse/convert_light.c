/*
** assign_light.c for assign_light in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 21 13:30:38 2017 Arthur Knoepflin
** Last update Fri Apr 21 13:47:47 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"

static int	nb_light(t_l_light *list)
{
  int		ret;

  ret = 0;
  while (list)
    {
      ret += 1;
      list = list->next;
    }
  return (ret);
}

static void	assign_light(t_light *light, t_l_light *list)
{
  light->pos = list->pos;
  light->col = list->col;
}

int	convert_light(t_params *par, t_l_light *list)
{
  int	i;

  par->nb_lights = nb_light(list);
  if ((par->lights = malloc(sizeof(t_light) * (nb_light(list)))) == NULL)
    return (1);
  i = 0;
  while (list)
    {
      assign_light(&(par->lights[i]), list);
      i += 1;
      list = list->next;
    }
  return (0);
}
