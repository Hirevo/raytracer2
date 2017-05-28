/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Sun May 28 12:33:47 2017 Arthur Knoepflin
*/

#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <limits.h>
#include "raytracer.h"
#include "solver.h"

char	*intersect = "intersect_cubet";
char	*normal = "get_normal_cubet";
char	*texture = "apply_tex_cubet";
int	id = 15;

static void	fill_equa(float *equa,
			  sfVector3f eye,
			  sfVector3f vec,
			  t_obj *obj)
{
  equa[0] = pow(vec.x, 4) + pow(vec.y, 4) + pow(vec.z, 4);
  equa[1] = 4 * (pow(vec.x, 3) * eye.x + pow(vec.y, 3) * eye.y +
    		 pow(vec.z, 3) * eye.z);
  equa[2] = 6 * (pow(vec.x, 2) * pow(eye.x, 2) +
    		 pow(vec.y, 2) * pow(eye.y, 2) +
    		 pow(vec.z, 2) * pow(eye.z, 2))
    - 5 * (pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
  equa[3] = 4 * (pow(eye.x, 3) * vec.x + pow(eye.y, 3) * vec.y +
    		 pow(eye.z, 3) * vec.z)
    - 10 * (eye.x * vec.x + eye.y * vec.y + eye.z * vec.z);
  equa[4] = (pow(eye.x, 4) + pow(eye.y, 4) +
    	     pow(eye.z, 4)) - 5 * (pow(eye.x, 2) +
				   pow(eye.y, 2) + pow(eye.z, 2));
}

float		intersect_cubet(sfVector3f eye,
				sfVector3f vec,
				t_obj *obj)
{
  float		min;
  float		equa[5];
  t_poly	*poly;
  t_solus	*solus;

  fill_equa(equa, eye, vec, obj);
  if ((poly = create_poly(5, equa[0], equa[1], equa[2], equa[3], equa[4]))
      == NULL)
    return (-1);
  solus = solver(poly);
  min = get_min_pos_solus(solus);
  del_polys(poly);
  del_solus(solus);
  return (min);
}

void		get_normal_cubet(t_thread *t, t_obj *obj)
{
  t->normal.x = 4 * pow(t->normal.x, 3) - 10 * t->normal.x;
  t->normal.y = 4 * pow(t->normal.y, 3) - 10 * t->normal.y;
  t->normal.z = 4 * pow(t->normal.z, 3) - 10 * t->normal.z;
}

sfColor		apply_tex_cubet(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
