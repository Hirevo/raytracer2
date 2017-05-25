/*
** solus_four_part2.c for solver in /home/cedric/Desktop/Solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 19:11:57 2017 
** Last update Thu May 25 13:54:29 2017 Cédric THOMAS
*/

#include <math.h>
#include "solver.h"

int		solver_four_part2(float *var, float *nxvar, t_solus *solus)
{
  float		delta_3;
  float		p3;
  float		p4;

  delta_3 = (nxvar[1] * nxvar[1]) - 2 * nxvar[0] + 4 * nxvar[2];
  p3 = -nxvar[1] / 2;
  if (var[1] <= 0)
    p3 *= -1;
  p4 = sqrt(fabs(delta_3)) / 2.0;
  if (delta_3 >= 0)
    {
      if (solus_add(solus, p3 + nxvar[3] + p4))
	return (1);      
      if (solus_add(solus, p3 + nxvar[3] - p4))
	return (1);
    }
  return (0);
}
