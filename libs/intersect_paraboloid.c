/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Sun Apr  9 15:15:37 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"
#include "inter.h"

char	*intersect = "intersect_parab";
char	*normal = "get_normal_parab";
char	*texture = "apply_tex_parab";
int	id = 14;

static double           delt(double a, double b, double c)
{
  return ((b * b) - (4 * a * c));
}

static double           solve(sfVector3f equa, double delta)
{
  double                msol1;
  double                msol2;

  if (delta == 0 && equa.x != 0)
    {
      msol1 = -equa.y / (2 * equa.x);
      return (msol1);
    }
  else if (delta > 0 && equa.x != 0)
    {
      msol1 = (-equa.y - sqrt(delta)) / (2 * equa.x);
      msol2 = (-equa.y + sqrt(delta)) / (2 * equa.x);
      if (msol2 > msol1 && msol1 > 0)
	return (msol1);
      else
	return (msol2);
    }
  return (-1);
}

float		intersect_parab(sfVector3f eye,
			sfVector3f vec,
			t_obj *obj)
{
  sfVector3f	equa;
  sfVector3f	up;
  float		sol;
  double	delta;

  up.x = 0;
  up.y = 0;
  up.z = 1;
  equa.x = dot(vec, vec) - pow(dot(vec, up), 2);
  equa.y = 2 * (dot(vec, eye) - dot(vec, up) *(dot(eye, up) + 2 * obj->p1.x));
  equa.z = dot(eye, eye) - dot(eye, up) *(dot(eye, up) + 4 * obj->p1.x);
  delta = delt(equa.x, equa.y, equa.z);
  if ((sol = solve(equa, delta)) < 0)
    return (-1);
  return (sol);
}

void		get_normal_parab(t_thread *t, t_obj *obj)
{
  float		m;
  sfVector3f	up;

  up.x = 0;
  up.y = 0;
  up.z = 1;
  m = dot(t->normal, up);
  t->normal.x = t->normal.x - up.x * (m + obj->p1.x);
  t->normal.y = t->normal.y - up.y * (m + obj->p1.x);
  t->normal.z = t->normal.z - up.z * (m + obj->p1.x);
  t->normal = normalize(t->normal);
}

sfColor		apply_tex_parab(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
