/*
** intersect_disk.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Feb 10 14:42:42 2017 Nicolas Polomack
** Last update Sat Apr  1 02:27:34 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

char	*intersect = "intersect_disk";
char	*normal = "get_normal_disk";
int	id = 8;

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

void	get_normal_disk(t_thread *t, t_obj *obj)
{
  get_normal_plane(t, obj);
}
