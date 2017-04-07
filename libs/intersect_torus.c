/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Tue Apr  4 23:20:31 2017 
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "inter.h"

char	*intersect = "intersect_torus";
char	*normal = "get_normal_torus";
int	id = 11;

float		fct(t_poly p, double x)
{
  int		i;
  int		deg;
  float		ret;

  i = -1;
  ret = 0;
  deg = p.elem - 1;
  while (++i < p.elem)
    {
      ret += p.coef[deg] * pow(x, deg);
      deg -= 1;
    }
  return (ret);
}

float		dico(t_poly poly)
{
  int		i;
  float		x;
  float		g;
  float		d;

  g = 0;
  d = 1;
  x = 0.5;
  i = 0;
  while (fabs(fct(poly, x)) >= pow(10, -PRECISION) && ++i < SECUR)
    {
      x = (g + d) / 2;
      if (fct(poly, g) * fct(poly, x) > 0)
	g = x;
      else
	d = x;
    }
  return (x);
}

float		intersect_torus(sfVector3f eye_pos,
			sfVector3f dir_vector,
			t_obj *obj)
{
  float		g;
  float		h;
  float		i;
  float		j;
  float		k;
  float		l;
  t_poly	poly;
  float		sol;

  poly.elem = 5;
  g = 4 * pow(obj->p1.x, 2) * (pow(dir_vector.x, 2) + pow(dir_vector.y, 2));
  h = 8 * pow(obj->p1.x, 2) * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y);
  i = 4 * pow(obj->p1.x, 2) * (pow(eye_pos.x, 2) + pow(eye_pos.y, 2));
  j = pow(dir_vector.x, 2) + pow(dir_vector.y, 2) + pow(dir_vector.z, 2);
  k = 2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y + eye_pos.z * dir_vector.z);
  l = pow(eye_pos.x, 2) + pow(eye_pos.y, 2) + pow(eye_pos.y, 2) +
    (pow(obj->p1.x, 2) - pow(obj->p1.y, 2)) ;
  poly.coef[0] = pow(j, 2);
  poly.coef[1] = 2 * j * k;
  poly.coef[2] = 2 * j * l + pow(k, 2) - g;
  poly.coef[3] = 2 * k * l - h;
  poly.coef[4] = pow(l, 2) - i;
  return (dico(poly));
}

void		get_normal_torus(t_thread *t, t_obj *obj)
{
 
}
