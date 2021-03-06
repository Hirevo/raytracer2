/*
** solus_four_part1.c for solus_four_part1 in /home/arthur/delivery/MUL/Solver/fourth
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 29 19:10:52 2017 Arthur Knoepflin
** Last update Thu May 25 13:54:21 2017 Cédric THOMAS
*/

#include <math.h>
#include "solver.h"

int	solver_four_part1(float *var, float *nxvar, t_solus *solus)
{
  float	delta_2;
  float	p1;
  float p2;

  delta_2 = (nxvar[1] * nxvar[1]) - (2.0 * nxvar[0]) - (4.0 * nxvar[2]);
  p1 = nxvar[1] / 2.0;
  if (var[1] <= 0)
    p1 *= -1;
  p2 = sqrt(fabs(delta_2)) / 2.0;
  if (delta_2 >= 0)
    {
      if (solus_add(solus, p1 + nxvar[3] + p2))
	return (1);
      if (solus_add(solus, p1 + nxvar[3] - p2))
	return (1);
    }
  return (0);
}
