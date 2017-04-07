/*
** intersect_triangle.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 20:58:54 2017 Nicolas Polomack
** Last update Wed Apr  5 19:41:33 2017 Nicolas Polomack
*/

#include <math.h>
#include "libs.h"
#include "sfcaster.h"
#include "raytracer.h"

char	*intersect = "intersect_triangle";
char	*normal = "get_normal_triangle";
char	*texture = "apply_tex_triangle";
int	id = 10;

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
  float		k1;
  float		k2;
  float		den;

  if ((sol = intersect_plane(eye_p, dir_vector, obj)) == -1)
    return (-1);
  i = create_vet2(dir_vector.x * sol + eye_p.x, dir_vector.y * sol +
                  eye_p.y);
  den = powf(dot2(obj->p1, obj->p2), 2) -
    dot2(obj->p1, obj->p1) * dot2(obj->p2, obj->p2);
  k1 = (dot2(obj->p1, obj->p2) * dot2(i, obj->p2) -
	dot2(obj->p2, obj->p2) * dot2(i, obj->p1)) / den;
  k2 = (dot2(obj->p1, obj->p2) * dot2(i, obj->p1) -
	dot2(obj->p1, obj->p1) * dot2(i, obj->p2)) / den;
  if (k1 < 0 || k2 < 0)
    return (-1.0F);
  if ((k1 + k2) > 1)
    return (-1.0F);
  return (sol);
}

void	get_normal_triangle(t_thread *t, t_obj *obj)
{
  get_normal_plane(t, obj);
}

sfColor	apply_tex_triangle(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
