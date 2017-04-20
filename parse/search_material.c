/*
** search_material.c for search_material in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 20 21:46:21 2017 Arthur Knoepflin
** Last update Thu Apr 20 21:51:21 2017 Arthur Knoepflin
*/

#include "raytracer.h"
#include "my.h"

t_material	*search_material(char *name, t_material *list)
{
  t_material	*tmp;

  tmp = list;
  while (tmp)
    {
      if (!my_strcmp(name, tmp->name))
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
