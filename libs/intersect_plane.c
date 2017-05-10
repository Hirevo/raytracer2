/*
** intersect_plane.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:31:08 2017 Nicolas Polomack
** Last update Wed May 10 17:53:01 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"

char	*intersect = "intersect_plane";
char	*normal = "get_normal_plane";
char	*texture = "apply_tex_plane";
int	id = 2;

float	intersect_plane(sfVector3f eye_pos,
			sfVector3f dir_vector,
			t_obj *obj)
{
  float	k;

  (void)obj;
  if (!(dir_vector.z))
    if (eye_pos.z != 0)
      return (-1);
    else
      return (0);
  else
    {
      k = (-eye_pos.z / dir_vector.z);
      return ((k < 0) ? -1 : k);
    }
}

void	get_normal_plane(t_thread *t, t_obj *obj)
{
  t->normal.x = 0;
  t->normal.y = 0;
  t->normal.z = 1;
}

sfColor		apply_tex_plane(sfVector3f impact,
				t_obj *obj)
{
  sfColor       col;
  int           u;
  int           v;

  if (obj->buffer == NULL)
    return (obj->col);
  impact.x = fabsf(fmodf(impact.x, obj->buffer->width));
  impact.y = fabsf(fmodf(impact.y, obj->buffer->height));
  u = fabsf(fmodf((impact.x - obj->pos.x), obj->buffer->width));
  v = fabsf(fmodf((impact.y - obj->pos.y), obj->buffer->height));
  col.r = obj->buffer->pixels[(v * obj->buffer->width + u) * 4];
  col.g = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 1];
  col.b = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 2];
  col.a = 255;
  return (col);
}
