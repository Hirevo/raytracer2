/*
** intersect_closed_cone.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Apr  1 01:18:21 2017 Nicolas Polomack
** Last update Wed Apr  5 19:40:34 2017 Nicolas Polomack
*/

#include <math.h>
#include "libs.h"
#include "raytracer.h"

char	*intersect = "intersect_semi_cone";
char	*normal = "get_normal_semi_cone";
char	*texture = "apply_tex_semi_cone";
int	id = 6;

float	intersect_semi_cone(sfVector3f eye_pos,
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
  return (dist);
}

void	get_normal_semi_cone(t_thread *t, t_obj *obj)
{
  t->normal.z *= -tanr(obj->aper);
}

sfColor	apply_tex_semi_cone(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
