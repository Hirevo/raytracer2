/*
** add_material.c for add_material.c in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 23:14:47 2017 
** Last update Thu Apr 20 19:02:30 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static void	assign(t_material *new, t_material add)
{

  if (add.name)
    new->name = my_strdup(add.name);
  else
    new->name = NULL;
  new->type = add.type;
  if (add.path)
    new->path = my_strdup(add.path);
  else
    new->path = NULL;
  new->buf = add.buf;
  new->color = add.color;
  new->next = NULL;
}

int		add_material(t_material **list, t_material add)
{
  t_material	*sauv;
  t_material	*new;

  sauv = *list;
  if ((new = malloc(sizeof(t_material))) == NULL)
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
