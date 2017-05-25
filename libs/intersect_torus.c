/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Thu May 25 21:17:08 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "solver.h"

char	*intersect = "intersect_torus";
char	*normal = "get_normal_torus";
char	*texture = "apply_tex_torus";
int	id = 12;

static void	fill_var(float *var, sfVector3f eye,
			 sfVector3f dir, t_obj *obj)
{
  var[0] = 4 * pow(obj->p1.x, 2) * (pow(dir.x, 2) + pow(dir.y, 2));
  var[1] = 8 * pow(obj->p1.x, 2) *
    (eye.x * dir.x + eye.y * dir.y);
  var[2] = 4 * pow(obj->p1.x, 2) * (pow(eye.x, 2) + pow(eye.y, 2));
  var[3] = pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2);
  var[4] = 2 * (eye.x * dir.x + eye.y *
	   dir.y + eye.z * dir.z);
  var[5] = pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2) +
    (pow(obj->p1.x, 2) - pow(obj->p1.y, 2));
}

float		intersect_torus(sfVector3f eye_pos,
				sfVector3f dir_vector,
				t_obj *obj)
{
  float		min;
  float		equa[5];
  float		var[6];
  t_poly	*poly;
  t_solus	*solus;

  fill_var(var, eye_pos, dir_vector, obj);
  equa[0] = pow(var[3], 2);
  equa[1] = 2 * var[3] * var[4];
  equa[2] = 2 * var[3] * var[5] + pow(var[4], 2) - var[0];
  equa[3] = 2 * var[4] * var[5] - var[1];
  equa[4] = pow(var[5], 2) - var[2];
  if ((poly = create_poly(5, equa[0], equa[1], equa[2], equa[3], equa[4]))
      == NULL)
    return (-1);
  solus = solver(poly);
  min = get_min_pos_solus(solus);
  del_polys(poly);
  del_solus(solus);
  return (min);
}

void		get_normal_torus(t_thread *t, t_obj *obj)
{
  float		a;
  sfVector3f	n;

  a = 1.0 - (obj->p1.x / sqrt(pow(t->impact.y, 2) + pow(t->impact.z, 2)));
  n = v3f(t->impact.x, a * t->impact.y, a * t->impact.z);
  t->normal = normalize(n);
}

sfColor		apply_tex_torus(sfVector3f imp, t_obj *obj)
{
  return (obj->col);
}
