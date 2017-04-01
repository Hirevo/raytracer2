/*
** intersect_limited_plane.c for lel in /home/Maxime/delivery/MUL/raytracer2/intersect/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu Mar 30 21:42:40 2017 Maxime Jenny
** Last update Sat Apr  1 02:27:41 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdlib.h>
#include "raytracer.h"

char	*intersect = "intersect_limited_plane";
char	*normal = "get_normal_limited_plane";
int	id = 9;

sfVector3f	create_vet3(float x, float y, float z)
{
  sfVector3f	ret;

  ret.x = x;
  ret.y = y;
  ret.z = z;
  return (ret);
}

float		intersect_limited_plane(sfVector3f eye_p, sfVector3f dir_vector,
					t_obj *obj)
{
  float		sol;
  sfVector2f	i;

  if ((sol = intersect_plane(eye_p, dir_vector, obj)) == -1)
    return (-1);
  i = create_vet2(dir_vector.x * sol + eye_p.x, dir_vector.y * sol +
		  eye_p.y);
  if (obj->p1.x > 0 && (i.x > obj->p1.x || i.x < 0))
    return (-1.0F);
  if (obj->p2.y > 0 && (i.y > obj->p2.y || i.y < 0))
    return (-1.0F);
  return (sol);
}

float	get_normal_limited_plane(t_thread *t, t_obj *obj)
{
  get_normal_plane(t, obj);
}
