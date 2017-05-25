/*
** solver_four.c for solver in /home/cedric/Desktop/Solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 18:34:50 2017 
** Last update Tue May  9 13:53:33 2017 
*/
#include <stdlib.h>
#include <math.h>
#include "solver.h"

static void	fill_next_var(float *nxvar, float *var, float *poly, float u)
{
  nxvar[0] = var[0] / 3 + u;
  nxvar[1] = sqrt(nxvar[0] - var[0]);
  nxvar[2] = sqrt(pow(nxvar[0] / 2, 2) - var[2]);
  nxvar[3] = -poly[1] / (4 * poly[0]);
}

static void	fill_var(float *var, float *poly)
{
  float		z;

  z = poly[1] / (2 * poly[0]);
  var[0] = poly[2] / poly[0] - 3 * (pow(z, 2) / 2);
  var[1] = poly[3] / poly[0] + pow(z, 3) - (z * poly[2]) / poly[0];
  var[2] = poly[4] / poly[0] - 3 * pow(z, 4) / 16;
  var[2] += poly[2] * pow(z, 2) / (4 * poly[0]);
  var[2] -= (poly[3] * z) / (2 * poly[0]);
  var[3] = -2 * pow(var[0] / 3, 3) - var[1] * var[1];
  var[3] += (8.0  * var[0] * var[2]) / 3.0;
  var[4] = -(pow(var[0], 2) + 12 * var[2]) / 3;
}

static float	get_u(float *var, float delta)
{
  float		w;
  float		u;

  if (delta > 0)
    {
      w = pow(-var[3] / 2 + sqrt(delta), 1.0 / 3.0);
      u = w - (var[4] / (3 * w));
    }
  else if (delta == 0)
    {
      u = 3 * var[3] / var[4];
    }
  else
    {
      u = 2 * sqrt(-var[4] / 3) *
	cos(acos(-var[3] / (2 * pow(-var[4] / 3, 3.0 / 2.0))) / 3);
    }
  return (u);
}

t_solus		*solver_four(float *poly)
{
  t_solus	*solus;
  float		var[5];
  float		next_var[4];
  float		delta;
  float		u;

  if ((solus = init_solus()) == NULL)
    return (NULL);
  fill_var(var, poly);
  delta = pow(var[4] / 3, 3) + pow(var[3] / 2, 2);
  u = get_u(var, delta);
  fill_next_var(next_var, var, poly, u);
  if (solver_four_part1(var, next_var, solus))
    return (NULL);
  if (solver_four_part2(var, next_var, solus))
    return (NULL);
  return (solus);
}
