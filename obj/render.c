/*
** render.c for 42sh in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 10:09:40 2017 Nicolas Polomack
** Last update Sat May 27 13:57:36 2017 Nicolas Polomack
*/

#include <math.h>
#include "sfcaster.h"
#include "raytracer.h"

sfVector3f	sub_vect(sfVector3f *v1, sfVector3f *v2)
{
  sfVector3f	v3;

  v3.x = v2->x - v1->x;
  v3.y = v2->y - v1->y;
  v3.z = v2->z - v1->z;
  return (v3);
}

sfVector3f	get_normal_obj(t_thread *t, t_obj *obj)
{
  sfVector3f	edge1;
  sfVector3f	edge2;

  edge1 = sub_vect(&(obj->obj_parse->p2[t->idx]),
		   &(obj->obj_parse->p1[t->idx]));
  edge2 = sub_vect(&(obj->obj_parse->p3[t->idx]),
		   &(obj->obj_parse->p1[t->idx]));
  return (oppose(cross(edge1, edge2)));
}

float		intersect_obj_tri(sfVector3f *orig, sfVector3f *dir,
				  t_obj_file *file, int i)
{
  sfVector3f	pvec;
  sfVector3f	tvec;
  sfVector3f	qvec;
  sfVector3f	edge[2];
  float		uvtdet[4];
  float		inv_det;
  
  edge[0] = sub_vect(&(file->p2[i]), &(file->p1[i]));
  edge[1] = sub_vect(&(file->p3[i]), &(file->p1[i]));
  pvec = cross(*dir, edge[1]);
  uvtdet[3] = dot(edge[0], pvec);
  if (uvtdet[3] < 0.000001F && uvtdet[3] > -0.000001F)
    return (-1);
  inv_det = 1.0F / uvtdet[3];
  tvec = sub_vect(orig, &(file->p1[i]));
  uvtdet[0] = dot(tvec, pvec) * inv_det;
  if (uvtdet[0] < 0 || uvtdet[0] > 1)
    return (-1);
  qvec = cross(tvec, edge[0]);
  uvtdet[1] = dot(*dir, qvec) * inv_det;
  if (uvtdet[1] < 0 || (uvtdet[0] + uvtdet[1]) > 1)
    return (-1);
  return (dot(edge[1], qvec) * inv_det);
}

float		get_dist_obj(sfVector3f orig, sfVector3f dir,
			     t_obj_file *file, int *obj_idx)
{
  float		ret;
  float		tmp;
  int		idx;
  int		i;

  ret = -1;
  i = -1;
  while (++i < file->nb_poly)
    {
      tmp = intersect_obj_tri(&orig, &dir, file, i);
      if (tmp >= 0 && (ret == -1 || ret > tmp))
	{
	  *obj_idx = i;
	  ret = tmp;
	}
    }
  return (ret);
}
