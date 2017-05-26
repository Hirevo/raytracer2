/*
** get_pc_from_node.c for get_pc_from_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 20 09:38:51 2017 Arthur Knoepflin
** Last update Fri May 26 04:45:34 2017 Nicolas Polomack
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

float	get_float_from_node(char *obj, char *getter)
{
  float ret;

  ret = get_int_from_node(obj, getter);
  return (ret / 100.0);
}
