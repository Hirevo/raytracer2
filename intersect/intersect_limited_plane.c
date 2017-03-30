/*
** intersect_limited_plane.c for lel in /home/Maxime/delivery/MUL/raytracer2/intersect/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu Mar 30 21:42:40 2017 Maxime Jenny
** Last update Thu Mar 30 22:32:12 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdlib.h>
#include "raytracer.h"

sfVector3f	create_vet3(float x, float y, float z)
{
  sfVector3f	ret;

  ret.x = x;
  ret.y = y;
  ret.z = z;
  return (ret);
}

float		intersect_limited_plane(sfVector3f eye_p, sfVector3f dir_vector,
					t_obj *obj)
{
  float		sol;
  sfVector2f	i;

  if ((sol = intersect_plane(eye_p, dir_vector, obj)) == -1)
    return (-1);
  i = create_vet2(dir_vector.x * sol + eye_p.x, dir_vector.y * sol +
		  eye_p.y);
  if (obj->len.x > 0 && (i.x > obj->len.x || i.x < 0))
    return (-1.0F);
  if (obj->len.y > 0 && (i.y > obj->len.y || i.y < 0))
    return (-1.0F);
  return (sol);
}
