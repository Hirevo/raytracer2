/*
** intersect_limited_plane.c for lel in /home/Maxime/delivery/MUL/raytracer2/intersect/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu Mar 30 21:42:40 2017 Maxime Jenny
** Last update Thu Mar 30 21:43:16 2017 Maxime Jenny
*/

#include <math.h>
#include <stdlib.h>
#include "raytracer2.h"

float		intersect_plane_2(sfVector3f eye_p, sfVector3f dir_vector,
				float x, float y)
{
  float		sol;
  sfVector3f	i;

  if (dir_vector.z == 0)
    {
      if (eye_p.z == 0)
	return (0);
      else
	return (-1.0F);
    }
  sol = (eye_p.z * -1) / dir_vector.z;
  i = create_vet3(dir_vector.x * sol + eye_p.x, dir_vector.y * sol +
		  eye_p.y, dir_vector.z * sol + eye_p.z);
  if (x > 0 && (i.x > x || i.x < 0))
    return (-1.0F);
  if (y > 0 && (i.y > y || i.y < 0))
    return (-1.0F);
  return ((sol < 0) ? (-1) : (sol));
}
