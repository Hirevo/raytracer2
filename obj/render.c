/*
** render.c for 42sh in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 10:09:40 2017 Nicolas Polomack
** Last update Tue May 23 22:36:37 2017 Arthur Knoepflin
*/

#include <math.h>
#include "sfcaster.h"
#include "raytracer.h"

sfVector3f	sub_vect(sfVector3f v1, sfVector3f v2)
{
  sfVector3f	v3;

  v3.x = v2.x - v1.x;
  v3.y = v2.y - v1.y;
  v3.z = v2.z - v1.z;
  return (v3);
}

sfVector3f	get_normal_obj(t_thread *t, t_obj *obj)
{
  sfVector3f	edge1;
  sfVector3f	edge2;

  edge1 = sub_vect(obj->obj_parse->p2[t->idx],
		   obj->obj_parse->p1[t->idx]);
  edge2 = sub_vect(obj->obj_parse->p3[t->idx],
		   obj->obj_parse->p1[t->idx]);
  return (cross(edge1, edge2));
}

float		intersect_obj_tri(t_ray *ray, sfVector3f pos1,
				  sfVector3f pos2,
				  sfVector3f pos3)
{
  sfVector3f	pvec;
  sfVector3f	tvec;
  sfVector3f	qvec;
  sfVector3f	edge[2];
  float		uvtdet[4];

  edge[0] = sub_vect(pos2, pos1);
  edge[1] = sub_vect(pos3, pos1);
  pvec = cross(ray->dir, edge[1]);
  uvtdet[3] = dot(edge[0], pvec);
  if (uvtdet[3] < 0.00000001F)
    return (-1);
  tvec = sub_vect(ray->orig, pos1);
  uvtdet[0] = dot(tvec, pvec);
  if (uvtdet[0] < 0 || uvtdet[0] > uvtdet[3])
    return (-1);
  qvec = cross(tvec, edge[0]);
  uvtdet[1] = dot(ray->dir, qvec);
  if (uvtdet[1] < 0 || uvtdet[0] + uvtdet[1] > uvtdet[3])
    return (-1);
  uvtdet[2] = dot(edge[1], qvec) / uvtdet[3];
  return (uvtdet[2]);
}

float		get_dist_obj(t_thread *t, t_obj_file *file)
{
  float		ret;
  float		tmp;
  int		idx;
  int		i;

  ret = -1;
  i = -1;
  while (++i < file->nb_poly)
    {
      tmp = intersect_obj_tri(&t->ray, file->p1[i],
			      file->p2[i],
			      file->p3[i]);
      if (tmp != -1 && (ret == -1 || ret > tmp))
	{
	  t->idx = i;
	  ret = tmp;
	}
    }
  return (ret);
}

sfVector3f	calc_impact(t_thread *t, float dist)
{
  sfVector3f	ret;

  ret.x = t->ray.orig.x + t->ray.dir.x * dist;
  ret.y = t->ray.orig.y + t->ray.dir.y * dist;
  ret.z = t->ray.orig.z + t->ray.dir.z * dist;
  return (ret);
}

/* sfColor		render_obj_pixel(t_thread *t) */
/* { */
/*   float		dist; */
/*   sfColor	col; */
/*   float		diffuse; */

/*   if ((dist = get_dist_obj(t)) != -1) */
/*     { */
/*       t->impact = calc_impact(t, dist); */
/*       t->normal = get_normal_obj(t); */
/*       col = sfWhite; */
/*       diffuse = fmaxf(get_light_coef(t->normal, sub_vect(t->params->lights[0].pos, */
/* 							 t->impact)), 0); */
/*       col.r *= diffuse; */
/*       col.g *= diffuse; */
/*       col.b *= diffuse; */
/*       return (col); */
/*     }  */
/*   return (sfBlack); */
/* } */

/* void	render_obj(t_thread *t) */
/* { */
/*   t->screen_pos.x = t->offs.x - 1; */
/*   while (++t->screen_pos.x < t->end.x) */
/*     { */
/*       t->screen_pos.y = t->offs.y - 1; */
/*       while (++t->screen_pos.y < t->end.y) */
/*         /\* if (t->params->config.depth_rays > 1) *\/ */
/*         /\*   put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y, *\/ */
/*         /\*             dof(t, t->screen_pos.x, t->screen_pos.y)); *\/ */
/*         /\* else *\/ */
/* 	{ */
/* 	  t->ray.orig = t->start; */
/* 	  prepare_raytrace(t); */
/* 	  put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y, */
/* 		    render_obj_pixel(t)); */
/* 	} */
/*       if (t->params->config.live) */
/*         update_frame(t->w, &t->params->mutex, t->params->config.bmp); */
/*     } */
/* } */
