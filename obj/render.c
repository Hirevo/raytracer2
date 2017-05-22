/*
** render.c for 42sh in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 10:09:40 2017 Nicolas Polomack
** Last update Mon May 22 16:18:04 2017 Nicolas Polomack
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

sfVector3f	get_normal_obj(t_poly_obj *tri)
{
  return (cross(tri->edge1, tri->edge2));
}

float		intersect_obj_tri(t_ray *ray,
				  t_poly_obj *tri)
{
  sfVector3f	pvec;
  sfVector3f	tvec;
  sfVector3f	qvec;
  float		uvtdet[4];
  float		epsilon;

  epsilon = 0.000001;
  tri->edge1 = sub_vect(tri->pos2, tri->pos1);
  tri->edge2 = sub_vect(tri->pos3, tri->pos1);
  pvec = cross(ray->dir, tri->edge2);
  uvtdet[3] = dot(tri->edge1, pvec);
  if (uvtdet[3] < epsilon)
    return (-1);
  tvec = sub_vect(ray->orig, tri->pos1);
  uvtdet[0] = dot(tvec, pvec);
  if (uvtdet[0] < 0 || uvtdet[0] > uvtdet[3])
    return (-1);
  qvec = cross(tvec, tri->edge1);
  uvtdet[1] = dot(ray->dir, qvec);
  if (uvtdet[1] < 0 || uvtdet[0] + uvtdet[1] > uvtdet[3])
    return (-1);
  uvtdet[2] = dot(tri->edge2, qvec) / uvtdet[3];
  return (uvtdet[2]);
}

float		get_dist_obj(t_thread *t)
{
  float		ret;
  float		tmp;
  t_poly_obj	*head;

  ret = -1;
  head = t->params->obj_data->poly_list;
  while (head)
    {
      tmp = intersect_obj_tri(&t->ray, head);
      if (tmp != -1 && (ret == -1 || ret > tmp))
	{
	  t->tri = head;
	  ret = tmp;
	}
      head = head->next;
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

sfColor		render_obj_pixel(t_thread *t)
{
  float		dist;
  sfColor	col;
  float		diffuse;

  if ((dist = get_dist_obj(t)) != -1)
    {
      t->impact = calc_impact(t, dist);
      t->normal = get_normal_obj(t->tri);
      col = sfRed;
      diffuse = fmaxf(get_light_coef(t->normal, sub_vect(t->params->lights[0].pos, t->impact)), 0);
      col.r *= diffuse;
      col.g *= diffuse;
      col.b *= diffuse;
      return (col);
    } 
  return (sfBlack);
}

void	render_obj(t_thread *t)
{
  t_poly_obj *head;

  head = t->params->obj_data->poly_list;
  t->screen_pos.x = t->offs.x - 1;
  while (++t->screen_pos.x < t->end.x)
    {
      t->screen_pos.y = t->offs.y - 1;
      while (++t->screen_pos.y < t->end.y)
        /* if (t->params->config.depth_rays > 1) */
        /*   put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y, */
        /*             dof(t, t->screen_pos.x, t->screen_pos.y)); */
        /* else */
	{
	  t->ray.orig = t->start;
	  prepare_raytrace(t);
	  put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y,
		    render_obj_pixel(t));
	}
      if (t->params->config.live)
        update_frame(t->w, &t->params->mutex, t->params->config.bmp);
    }
}
