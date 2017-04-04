/*
** intersect_closed_cone.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Apr  1 01:18:21 2017 Nicolas Polomack
** Last update Tue Apr  4 18:49:53 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

char	*intersect = "intersect_closed_cone";
char	*normal = "get_normal_closed_cone";
int	id = 7;

float	intersect_closed_cone(sfVector3f eye_pos,
                              sfVector3f dir_vector,
                              t_obj *obj)
{
  float	impz;
  float	dist;

  if ((dist = intersect_cone(eye_pos, dir_vector, obj)) == -1)
    return (-1);
  impz = eye_pos.z + dir_vector.z * dist;
  if (roundf(impz) >= 0)
    return (-1);
  if (roundf(impz) >= -obj->height)
    return (dist);
  eye_pos.z += (obj->height);
  obj->rad = tanr(obj->aper) * obj->height;
  dist = intersect_disk(eye_pos, dir_vector, obj);
  return (dist);
}

void	get_normal_closed_cone(t_thread *t, t_obj *obj)
{
  if (roundf(t->normal.z) == -(obj->height) &&
      roundf(powf(t->normal.x, 2) + powf(t->normal.y, 2) -
	     powf(obj->rad, 2)) != 0)
    {
      t->normal.x = 0;
      t->normal.y = 0;
      t->normal.z = -100;
      return ;
    }
  t->normal.z *= -tanr(obj->aper);
}
