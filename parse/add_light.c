/*
** add_light.c for add_light in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 17:17:30 2017 Arthur Knoepflin
** Last update Tue Apr 18 20:35:05 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"

static void	assign(t_l_light *new, t_l_light add)
{
  new->next = NULL;
  new->pos = add.pos;
  new->col = add.col;
}

int		add_light(t_l_light **list, t_l_light add)
{
  t_l_light	*sauv;
  t_l_light	*new;

  sauv = *list;
  if ((new = malloc(sizeof(t_l_light))) == NULL)
    return (1);
  assign(new, add);
  if (*list)
    {
      while (sauv && sauv->next)
	sauv = sauv->next;
      sauv->next = new;
    }
  else
    *list = new;
  return (0);
}
