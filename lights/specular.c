/*
** specular.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Mar 29 00:28:22 2017 Nicolas Polomack
** Last update Tue Apr  4 19:56:50 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

float		get_specular_coef(t_thread *t, t_obj *obj, int i)
{
  float		f;
  sfVector3f	n;
  sfVector3f	reflect;

  n = normalize(t->normal);
  reflect = t->impact;
  reflect.x -= t->params->lights[i].pos.x;
  reflect.y -= t->params->lights[i].pos.y;
  reflect.z -= t->params->lights[i].pos.z;
  if ((f = -dot(n, reflect)) <= 0)
    return (0);
  reflect.x = reflect.x + (2.0F * n.x * f);
  reflect.y = reflect.y + (2.0F * n.y * f);
  reflect.z = reflect.z + (2.0F * n.z * f);
  n = t->recur_start;
  n.x -= t->impact.x;
  n.y -= t->impact.y;
  n.z -= t->impact.z;
  n = normalize(n);
  reflect = normalize(reflect);
  return (powf(dot(reflect, n), obj->spec_coef));
}

sfColor		specular_effect(sfColor col, t_thread *t, t_obj *obj, int l)
{
  int		i[3];
  float		coef;

  coef = fmax(0, get_specular_coef(t, obj, l)) * (!(obj->type));
  i[0] = (((float)col.r) + 255.0F * coef);
  i[1] = (((float)col.g) + 255.0F * coef);
  i[2] = (((float)col.b) + 255.0F * coef);
  if (i[0] > 255)
    i[0] = 255;
  if (i[1] > 255)
    i[1] = 255;
  if (i[2] > 255)
    i[2] = 255;
  col.r = i[0];
  col.g = i[1];
  col.b = i[2];
  col.a = 255;
  return (col);
}
