/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Wed Apr  5 19:38:36 2017 Nicolas Polomack
*/

#include <math.h>
#include "libs.h"
#include "raytracer.h"

char	*intersect = "intersect_cyl";
char	*normal = "get_normal_cyl";
char	*texture = "apply_tex_cyl";
int	id = 3;

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
  return (root[1]);
}

void	get_normal_cyl(t_thread *t, t_obj *obj)
{
  t->normal.z = 0;
}

sfColor	apply_tex_cyl(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
