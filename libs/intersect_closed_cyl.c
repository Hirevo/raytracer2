/*
** intersect_closed_cyl.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Apr  1 01:04:05 2017 Nicolas Polomack
** Last update Sat Apr  1 04:27:39 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

char	*intersect = "intersect_closed_cyl";
char	*normal = "get_normal_closed_cyl";
int	id = 4;

float		intersect_closed_cyl(sfVector3f eye_pos,
				     sfVector3f dir_vector, t_obj *obj)
{
  float		dist;
  sfVector3f	imp;

  if ((dist = intersect_cone(eye_pos, dir_vector, obj)) == -1)
    return (-1);
  imp.z = eye_pos.z + dir_vector.z * dist;
  if (imp.z <= (obj->height / 2) && imp.z >= -(obj->height / 2))
    return (dist);
  eye_pos.z -= (obj->height / 2);
  if ((dist = intersect_disk(eye_pos, dir_vector, obj)) != -1)
    return (dist);
  eye_pos.z += obj->height;
  if ((dist = intersect_disk(eye_pos, dir_vector, obj)) != -1)
    return (dist);
  eye_pos.z -= (obj->height / 2);
  return (-1);
}

void	get_normal_closed_cyl(t_thread *t, t_obj *obj)
{
  if (roundf(powf(t->normal.x, 2) + powf(t->normal.y, 2) -
             powf(obj->rad, 2)) != 0)
    {
      if (roundf(t->normal.z) == (obj->height / 2))
        {
          t->normal.x = 0;
          t->normal.y = 0;
          t->normal.z = 100;
          return ;
        }
      else if (roundf(t->normal.z) == -(obj->height / 2))
        {
          t->normal.x = 0;
          t->normal.y = 0;
          t->normal.z = -100;
          return ;
        }
    }
  t->normal.z = 0;
}
