/*
** normals.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Feb 10 22:55:04 2017 Nicolas Polomack
** Last update Mon Mar 27 02:10:46 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"
#include "sfcaster.h"

void	get_normal_cone(t_params *params, t_obj *obj)
{
  if (obj->type == 6 &&
      roundf(params->normal.z) == (obj->height) &&
      roundf(powf(params->normal.x, 2) + powf(params->normal.y, 2) -
	     powf(obj->rad, 2)) != 0)
    {
      params->normal.x = 0;
      params->normal.y = 0;
      params->normal.z = -100;
      return ;
    }
  params->normal.z *= -tanr(obj->aper);
}

void	get_normal_cyl(t_params *params, t_obj *obj)
{
  if (obj->type == 3 &&
      roundf(powf(params->normal.x, 2) + powf(params->normal.y, 2) -
	     powf(obj->rad, 2)) != 0)
    {
      if (roundf(params->normal.z) == (obj->height / 2))
	{
	  params->normal.x = 0;
	  params->normal.y = 0;
	  params->normal.z = 100;
	  return ;
	}
      else if (roundf(params->normal.z) == -(obj->height / 2))
	{
	  params->normal.x = 0;
	  params->normal.y = 0;
	  params->normal.z = -100;
	  return ;
	}
    }
  params->normal.z = 0;
}

void	get_normal_plane(t_params *params, t_obj *obj)
{
  (void)obj;
  params->normal.x = 0;
  params->normal.y = 0;
  params->normal.z = 1;
}

void	get_normal_sphere(t_params *params, t_obj *obj)
{
  (void)params;
  (void)obj;
  return ;
}
