/*
1;4601;0c1;4601;0c** intersect_triangle.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 20:58:54 2017 Nicolas Polomack
** Last update Fri Mar 31 00:02:28 2017 Nicolas Polomack
*/

#include <math.h>
#include "sfcaster.h"
#include "raytracer.h"

float		norm2(sfVector2f i)
{
  return (sqrtf(i.x * i.x + i.y * i.y));
}

float		dot2(sfVector2f u, sfVector2f v)
{
  return (u.x * v.x + u.y * v.y);
}

sfVector2f	create_vet2(float x, float y)
{
  sfVector2f	ret;

  ret.x = x;
  ret.y = y;
  return (ret);
}

float		intersect_triangle(sfVector3f eye_p, sfVector3f dir_vector,
				   t_obj *obj)
{
  float		sol;
  sfVector2f	i;
  sfVector2f	u;
  sfVector2f	v;
  float		k1;
  float		k2;
  float		den;

  if ((sol = intersect_plane(eye_p, dir_vector, obj)) == -1)
    return (-1);
  i = create_vet2(dir_vector.x * sol + eye_p.x, dir_vector.y * sol +
                  eye_p.y);
  u = create_vet2(obj->len.x, 0);
  v = create_vet2(0, obj->len.y);
  den = powf(dot2(u, v), 2) - dot2(u, u) * dot2(v, v);
  k1 = (dot2(u, v) * dot2(i, v) - dot2(v, v) * dot2(i, u)) / den;
  k2 = (dot2(u, v) * dot2(i, u) - dot2(u, u) * dot2(i, v)) / den;
  if (k1 < 0 || k2 < 0)
    return (-1.0F);
  if ((k1 + k2) > 1)
    return (-1.0F);
  return (sol);
}
