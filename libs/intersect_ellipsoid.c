/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Fri Apr  7 16:47:09 2017 
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"
#include "inter.h"

char	*intersect = "intersect_elli";
char	*normal = "get_normal_elli";
int	id = 13;

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

float		intersect_elli(sfVector3f eye,
			sfVector3f vec,
			t_obj *obj)
{
  float		denom;
  float		a;
  float		b;
  float		c;
  sfVector3f    equa;
  float         sol;
  double        delta;

  if ((obj->p1.x * obj->p1.y * obj->p2.x) == 0)
    return (-1);
  a = obj->p1.x;
  b = obj->p1.y;
  c = obj->p2.x;
  denom = pow(a * b * c, 2);
  equa.x = (pow(vec.x * c * b, 2) + pow(vec.y * c * a, 2)
	    + pow(vec.z * b * a, 2)) / denom;
  equa.y = 2 * (eye.x * vec.x * pow(c * b, 2) + eye.y * vec.y * pow(c * a, 2)
		+ eye.z * vec.z * pow(b * a, 2)) / denom;
  equa.z = (pow(eye.x * c * b, 2) + pow(eye.y * c * a, 2)
	    + pow(eye.z * b * a, 2)) / denom - 1;
  delta = delt(equa.x, equa.y, equa.z);
  if ((sol = solve(equa, delta)) < 0)
    return (-1);
  return (sol);
}

void		get_normal_elli(t_thread *t, t_obj *obj)
{
  if ((obj->p1.x * obj->p1.y * obj->p2.x) == 0)
    return ;
  t->normal.x /= pow(obj->p1.x, 2);
  t->normal.y /= pow(obj->p1.y, 2);
  t->normal.z /= pow(obj->p2.x, 2);
}
