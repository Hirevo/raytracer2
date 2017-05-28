/*
** get_normal_cube.c for intersect_cube in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun May 28 18:05:56 2017 Nicolas Polomack
** Last update Sun May 28 18:07:01 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <math.h>
#include "sfcaster.h"
#include "raytracer.h"

void	get_normal_cube(t_thread *t, t_obj *obj)
{
  if (fabsf(t->normal.x - obj->rad) < 0.01)
    t->normal = v3f(1, 0, 0);
  else if (fabsf(t->normal.x + obj->rad) < 0.01)
    t->normal = v3f(-1, 0, 0);
  else if (fabsf(t->normal.y - obj->rad) < 0.01)
    t->normal = v3f(0, 1, 0);
  else if (fabsf(t->normal.y + obj->rad) < 0.01)
    t->normal = v3f(0, -1, 0);
  else if (fabsf(t->normal.z - obj->rad) < 0.01)
    t->normal = v3f(0, 0, 1);
  else if (fabsf(t->normal.z + obj->rad) < 0.01)
    t->normal = v3f(0, 0, -1);
}

sfColor	apply_tex_cube(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
