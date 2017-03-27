/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Mon Mar 27 03:01:38 2017 Nicolas Polomack
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
  else if (root[1] < 0)
    return (-1);
  return (root[1]);
}

float		intersect_cyl(sfVector3f eye_pos,
			      sfVector3f dir_vector,
			      t_obj *obj)
{
  float		a;
  float		b;
  float		c;
  float		delta;
  float		root[2];

  root[1] = -1;
  a = powf(dir_vector.x, 2) + powf(dir_vector.y, 2);
  b = (2 * eye_pos.x * dir_vector.x + 2 * eye_pos.y * dir_vector.y);
  c = (powf(eye_pos.x, 2) + powf(eye_pos.y, 2) - powf(obj->rad, 2));
  delta = b * b - 4 * a * c;
  if (delta <= 0)
    return (-1.0F);
  else if (delta)
    {
      delta = sqrtf(delta);
      root[0] = (-b - delta) / (2 * a);
      root[1] = (-b + delta) / (2 * a);
      root[1] = get_value(root);
    }
  if (root[1] == -1)
    return (-1);
  if (obj->type == 3)
    return (intersect_closed_cyl(eye_pos, dir_vector, obj, root[1]));
  return (root[1]);
}

float		intersect_closed_cyl(sfVector3f eye_pos,
				     sfVector3f dir_vector,
				     t_obj *obj, float dist)
{
  sfVector3f	imp;

  imp.x = eye_pos.x + dir_vector.x * dist;
  imp.y = eye_pos.y + dir_vector.y * dist;
  imp.z = eye_pos.z + dir_vector.z * dist;
  if (imp.z <= (obj->height / 2) && imp.z >= -(obj->height / 2))
    return (dist);
  eye_pos.z -= (obj->height / 2);
  if ((dist = intersect_disk(eye_pos, dir_vector, obj)) != -1)
    {
      eye_pos.z += (obj->height / 2);
      return (dist);
    }
  eye_pos.z += obj->height;
  if ((dist = intersect_disk(eye_pos, dir_vector, obj)) != -1)
    {
      eye_pos.z -= (obj->height / 2);
      return (dist);
    }
  eye_pos.z -= (obj->height / 2);
  return (-1);
}
