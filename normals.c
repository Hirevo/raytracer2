/*
** normals.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Feb 10 22:55:04 2017 Nicolas Polomack
** Last update Tue Mar 28 18:38:21 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"
#include "sfcaster.h"

void	get_normal_cone(t_thread *t, t_obj *obj)
{
  if (obj->type == 6 &&
      roundf(t->normal.z) == (obj->height) &&
      roundf(powf(t->normal.x, 2) + powf(t->normal.y, 2) -
	     powf(obj->rad, 2)) != 0)
    {
      t->normal.x = 0;
      t->normal.y = 0;
      t->normal.z = -100;
      return ;
    }
  t->normal.z *= -tanr(obj->aper);
}

void	get_normal_cyl(t_thread *t, t_obj *obj)
{
  if (obj->type == 3 &&
      roundf(powf(t->normal.x, 2) + powf(t->normal.y, 2) -
	     powf(obj->rad, 2)) != 0)
    {
      if (roundf(t->normal.z) == (obj->height / 2))
	{
	  t->normal.x = 0;
	  t->normal.y = 0;
	  t->normal.z = 100;
	  return ;
	}
      else if (roundf(t->normal.z) == -(obj->height / 2))
	{
	  t->normal.x = 0;
	  t->normal.y = 0;
	  t->normal.z = -100;
	  return ;
	}
    }
  t->normal.z = 0;
}

void	get_normal_plane(t_thread *t, t_obj *obj)
{
  (void)obj;
  t->normal.x = 0;
  t->normal.y = 0;
  t->normal.z = 1;
}

void	get_normal_sphere(t_thread *t, t_obj *obj)
{
  (void)t;
  (void)obj;
  return ;
}
