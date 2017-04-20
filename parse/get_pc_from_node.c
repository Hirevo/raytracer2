/*
** get_pc_from_node.c for get_pc_from_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 20 09:38:51 2017 Arthur Knoepflin
** Last update Thu Apr 20 09:56:50 2017 Arthur Knoepflin
*/

#include "raytracer.h"

float	get_pc_from_node(char *obj, char *getter)
{
  float	ret;

  ret = get_int_from_node(obj, getter);
  if (ret <= 0)
    return (0);
  if (ret >= 100)
    return (1);
  return (ret / 100.0);
}
