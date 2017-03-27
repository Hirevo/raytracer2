/*
** intersect_disk.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Feb 10 14:42:42 2017 Nicolas Polomack
** Last update Mon Mar 27 00:32:50 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

float		intersect_disk(sfVector3f eye_pos,
			       sfVector3f dir_vector,
			       t_obj *obj)
{
  float		dist;
  float		res;
  sfVector3f	imp;

  if ((dist = intersect_plane(eye_pos, dir_vector, obj)) != -1)
    {
      imp.x = eye_pos.x + dir_vector.x * dist;
      imp.y = eye_pos.y + dir_vector.y * dist;
      imp.z = powf(imp.x, 2) + powf(imp.y, 2);
      res = (roundf(imp.z) <= roundf(powf(obj->rad, 2))) ? dist : -1;
      return (res);
    }
  return (-1);
}
