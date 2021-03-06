/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Wed Apr  5 19:44:14 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"

char	*intersect = "intersect_sphere";
char	*normal = "get_normal_sphere";
char	*texture = "apply_tex_sphere";
int	id = 1;

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

void	get_normal_sphere(t_thread *t, t_obj *obj)
{
}

sfColor		apply_tex_sphere(sfVector3f vp, t_obj *obj)
{
  float		phi;
  float		theta;
  int		u;
  int		v;
  sfColor	col;
  sfVector3f	ve;
  sfVector3f	vn;

  if (obj->buffer == NULL)
    return (obj->col);
  vp = normalize(vp);
  ve = v3f(0, 1, 0);
  vn = v3f(0, 0, 1);
  phi = acos(-1 * dot(vn, vp));
  theta = (acos(dot(vp, ve) / sin(phi))) / (2 * M_PI);
  v = phi * obj->buffer->height / M_PI;
  if (dot(cross(vn, ve), vp) > 0)
    u = theta * obj->buffer->width;
  else
    u = (1 - theta) * obj->buffer->width;
  col.r = obj->buffer->pixels[(v * obj->buffer->width + u) * 4];
  col.g = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 1];
  col.b = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 2];
  col.a = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 3];
  return (col);
}
