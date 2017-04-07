/*
** refract.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Apr  6 10:47:16 2017 Nicolas Polomack
** Last update Fri Apr  7 16:58:30 2017 Nicolas Polomack
*/

#include "raytracer.h"

sfVector3f	oppose(sfVector3f v)
{
  sfVector3f	ret;

  ret.x = v.x;
  ret.y = v.y;
  ret.z = v.z;
  return (ret);
}

void	prepare_refract(t_thread *t, float c1,
			float n2)
{
  float	n;
  float	n1;
  float	c2;

  n1 = 1;
  t->ray.orig = t->impact;
  t->ray.orig.x += t->ray.dir.x * 0.01;
  t->ray.orig.y += t->ray.dir.y * 0.01;
  t->ray.orig.z += t->ray.dir.z * 0.01;
  t->normal = normalize(t->normal);
  t->ray.dir = normalize(t->ray.dir);
  c1 = dot(t->ray.dir, t->normal);
  if (c1 < 0)
    c1 = -c1;
  n = n2 / n1;
  c2 = sqrtf(1 + (n * n) * ((c1 * c1) - 1));
  t->ray.dir.x = (n * t->ray.dir.x) + (n * c1 - c2) * t->normal.x;
  t->ray.dir.y = (n * t->ray.dir.y) + (n * c1 - c2) * t->normal.y;
  t->ray.dir.z = (n * t->ray.dir.z) + (n * c1 - c2) * t->normal.z;
}
