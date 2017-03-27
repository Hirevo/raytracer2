/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Mon Mar 27 00:30:08 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"

static float	get_value(float root[2])
{
  if (root[0] > 0)
    if (root[1] > 0)
      return ((root[0] > root[1]) ? root[1] : root[0]);
    else
      return (root[0]);
  else
    return ((root[1] > 0) ? root[1] : -1);
}

float	intersect_sphere(sfVector3f eye_pos,
			 sfVector3f dir_vector,
			 t_obj *obj)
{
  float	a;
  float	b;
  float	c;
  float	delta;
  float	root[2];

  a = powf(dir_vector.x, 2) + powf(dir_vector.y, 2) +
    powf(dir_vector.z, 2);
  b = (2 * eye_pos.x * dir_vector.x + 2 * eye_pos.y *
       dir_vector.y + 2 * eye_pos.z * dir_vector.z);
  c = (powf(eye_pos.x, 2) + powf(eye_pos.y, 2) +
       powf(eye_pos.z, 2) - powf(obj->rad, 2));
  delta = b * b - 4 * a * c;
  if (delta < 0)
    return (-1.0F);
  else if (delta)
    {
      delta = sqrtf(delta);
      root[0] = (-b - delta) / (2 * a);
      root[1] = (-b + delta) / (2 * a);
      return (get_value(root));
    }
  else
    return (-b / (2 * a));
}
