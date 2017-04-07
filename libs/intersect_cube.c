/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Fri Apr  7 14:20:21 2017 Nicolas Polomack
*/

#include <float.h>
#include <math.h>
#include "libs.h"
#include "my.h"
#include "raytracer.h"

char	*intersect = "intersect_cube";
char	*normal = "get_normal_cube";
char	*texture = "apply_tex_cube";
int	id = 11;

static int	x_plane(sfVector3f eye, sfVector3f dir,
			t_obj *obj, float *t)
{
  float		t1;
  float		t2;
  int		inter;

  inter = 1;
  if (dir.x == 0)
    if (eye.x < -obj->rad || eye.x > obj->rad)
      return (-1);
  t1 = ((-obj->rad) - eye.x) / dir.x;
  t2 = (obj->rad - eye.x) / dir.x;
  if (t1 > t2)
    swap_f(&t1, &t2);
  if (t1 > t[0])
    t[0] = t1;
  if (t2 < t[1])
    t[1] = t2;
  if (t[0] > t[1])
    inter = 0;
  if (t[1] < 0)
    inter = 0;
  return (inter);
}

static int	y_plane(sfVector3f eye, sfVector3f dir,
			t_obj *obj, float *t)
{
  float		t1;
  float		t2;
  int		inter;

  inter = 1;
  if (dir.y == 0)
    if (eye.y < -obj->rad || eye.y > obj->rad)
      return (-1);
  t1 = ((-obj->rad) - eye.y) / dir.y;
  t2 = (obj->rad - eye.y) / dir.y;
  if (t1 > t2)
    swap_f(&t1, &t2);
  if (t1 > t[0])
    t[0] = t1;
  if (t2 < t[1])
    t[1] = t2;
  if (t[0] > t[1])
    inter = 0;
  if (t[1] < 0)
    inter = 0;
  return (inter);
}

static int	z_plane(sfVector3f eye, sfVector3f dir,
			t_obj *obj, float *t)
{
  float		t1;
  float		t2;
  int           inter;

  inter = 1;
  if (dir.z == 0)
    if (eye.z < -obj->rad || eye.z > obj->rad)
      return (-1);
  t1 = ((-obj->rad) - eye.z) / dir.z;
  t2 = (obj->rad - eye.z) / dir.z;
  if (t1 > t2)
    swap_f(&t1, &t2);
  if (t1 > t[0])
    t[0] = t1;
  if (t2 < t[1])
    t[1] = t2;
  if (t[0] > t[1])
    inter = 0;
  if (t[1] < 0)
    inter = 0;
  return (inter);
}

float	intersect_cube(sfVector3f eye,
		       sfVector3f dir,
		       t_obj *obj)
{
  float	near;
  int	eval;
  float	t[2];

  near = -1;
  eval = 1;
  t[0] = -1;
  t[1] = FLT_MAX;
  eval &= x_plane(eye, dir, obj, t);
  eval &= y_plane(eye, dir, obj, t);
  eval &= z_plane(eye, dir, obj, t);
  if (eval == 1)
    return (t[0]);
  else
    return (-1);
}

void		get_normal_cube(t_thread *t, t_obj *obj)
{
  if (fabsf(t->normal.x - obj->rad) < 0.01)
    t->normal = v3f(1, 0, 0);
  else if (fabsf(t->normal.x + obj->rad) < 0.01)
    t->normal = v3f(-1, 0, 0);
  else if (fabsf(t->normal.y - obj->rad) < 0.01)
    t->normal = v3f(0, 1, 0);
  else if (fabsf(t->normal.y + obj->rad) < 0.01)
    t->normal = v3f(0, -1, 0);
  else if (fabsf(t->normal.z - obj->rad) < 0.01)
    t->normal = v3f(0, 0, 1);
  else if (fabsf(t->normal.z + obj->rad) < 0.01)
    t->normal = v3f(0, 0, -1);
}

sfColor	apply_tex_cube(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
