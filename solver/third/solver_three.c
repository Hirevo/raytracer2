/*
** solver_three.c for solver in /home/cedric/Desktop/solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 15:18:22 2017 
** Last update Sat Apr 29 21:47:09 2017 
*/
#include <math.h>
#include <stdlib.h>
#include "solver.h"

static t_solus		*d_neg(float *var, t_solus *solus)
{
  float			u;
  float			v;
  float			t;

  u = 2 * sqrt(-var[4] / 3.0);
  v =  -var[5] / (2 *pow((-var[4] / 3.0), 3.0 / 2.0));
  t = acos(v) / 3;
  if (solus_add(solus, u * cos(t) - var[3]))
    return (NULL);
  if (solus_add(solus, u * cos(t + 4.0 * M_PI / 3.0) - var[3]))
    return (NULL);
  if (solus_add(solus, u * cos(t + 2.0 * M_PI / 3.0) - var[3]))
    return (NULL);
  return (solus);
}

static t_solus		*d_pos(float *var, t_solus *solus, float delta)
{
  float			w;
  float			x1;

  w = cbrt(-var[5] / 2 + sqrt(delta));
  if (w == 0)
    return (NULL);
  x1 = w - (var[4] / (3 * w)) - var[3];
  if (solus_add(solus, x1))
    return (NULL);
  return (solus);
}

static t_solus		*d_null(float *var, t_solus *solus)
{
  float			x1;
  float			x2;

  if (var[4] == 0)
    return (NULL);
  x1 = 3 * var[5] / var[4] - var[3];
  x2 = -3 * var[5] / (2 * var[4]) - var[3];
  if (solus_add(solus, x1))
    return (NULL);
  if (solus_add(solus, x2))
    return (NULL);
  return (solus);
}

static void		fill_temp(float *poly, float *var)
{
  var[0] = poly[3] / poly[0];
  var[1] = poly[2] / poly[0];
  var[2] = poly[1] / poly[0];
  var[3] = var[2] / 3;
  var[4] = var[1] - (var[2] * var[3]);
  var[5] = var[0] - (var[1] * var[3]) + 2 * pow(var[3], 3);
}

t_solus		*solver_three(float *poly)
{
  t_solus	*solus;
  float		var[6];
  float		delta;

  if ((solus = init_solus()) == NULL)
    return (NULL);
  if (poly[1] == poly[2] && poly[1] == 0)
    {
      if (solus_add(solus, cbrt(-poly[3] / poly[0])))
	return (NULL);
      return (solus);
    }
  fill_temp(poly, var);
  delta = pow(var[5] / 2, 2) + pow(var[4] / 3, 3);
  if (delta == 0)
    return (d_null(var, solus));
  else if (delta < 0)
    return (d_neg(var, solus));
  else
    return (d_pos(var, solus, delta));
}
